# Strike Gundam Test Runner for Windows PowerShell
# STM32 embedded development with Google Test framework

param(
    [string]$TestType = "all",
    [string]$TestCase = "",
    [switch]$Verbose = $false,
    [switch]$Coverage = $false,
    [switch]$Help = $false
)

# カラー出力関数
function Write-ColorOutput($ForegroundColor) {
    $fc = $host.UI.RawUI.ForegroundColor
    $host.UI.RawUI.ForegroundColor = $ForegroundColor
    if ($args) {
        Write-Output $args
    } else {
        $input | Write-Output
    }
    $host.UI.RawUI.ForegroundColor = $fc
}

# ヘルプ表示
function Show-Help {
    Write-ColorOutput Green "Strike Gundam Test Runner"
    Write-ColorOutput Green "========================"
    Write-Output ""
    Write-Output "Usage: .\run_tests.ps1 [options]"
    Write-Output ""
    Write-Output "Options:"
    Write-Output "  -TestType <type>    Test type to run (all, unit, integration, build)"
    Write-Output "  -TestCase <name>    Specific test case to run"
    Write-Output "  -Verbose           Enable verbose output"
    Write-Output "  -Coverage          Generate coverage report (requires gcov)"
    Write-Output "  -Help              Show this help"
    Write-Output ""
    Write-Output "Examples:"
    Write-Output "  .\run_tests.ps1                              # Run all tests"
    Write-Output "  .\run_tests.ps1 -TestType unit               # Run unit tests only"
    Write-Output "  .\run_tests.ps1 -TestCase 'StrikeSystemTest.*' # Run specific test case"
    Write-Output "  .\run_tests.ps1 -Verbose                     # Run with verbose output"
}

if ($Help) {
    Show-Help
    exit 0
}

# プロジェクトルートディレクトリの確認
$ProjectRoot = Split-Path -Parent $PSScriptRoot
$TestDir = $PSScriptRoot
$BuildDir = Join-Path $TestDir "build"

Write-ColorOutput Cyan "Strike Gundam Test Environment"
Write-ColorOutput Cyan "=============================="
Write-Output "Project Root: $ProjectRoot"
Write-Output "Test Directory: $TestDir"
Write-Output "Build Directory: $BuildDir"
Write-Output ""

# ビルドディレクトリ作成
if (-not (Test-Path $BuildDir)) {
    New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null
    Write-ColorOutput Yellow "Created build directory: $BuildDir"
}

# CMakeが利用可能かチェック
try {
    $cmake_version = & cmake --version 2>$null
    if ($LASTEXITCODE -eq 0) {
        Write-ColorOutput Green "CMake detected: Using CMake build system"
        $UseCMake = $true
    } else {
        $UseCMake = $false
    }
} catch {
    $UseCMake = $false
}

# Google Testライブラリの確認
function Test-GoogleTestAvailable {
    try {
        # vcpkg経由での確認
        $vcpkg_installed = Test-Path "$env:VCPKG_ROOT\installed\x64-windows\include\gtest"
        if ($vcpkg_installed) {
            Write-ColorOutput Green "Google Test found via vcpkg"
            return $true
        }
        
        # システムにインストールされている場合の確認
        $system_gtest = Test-Path "C:\Program Files\googletest"
        if ($system_gtest) {
            Write-ColorOutput Green "Google Test found in system path"
            return $true
        }
        
        Write-ColorOutput Yellow "Google Test not found. Please install via vcpkg or manually."
        Write-Output "Install command: vcpkg install gtest:x64-windows"
        return $false
    } catch {
        return $false
    }
}

# Google Test可用性チェック
$GTestAvailable = Test-GoogleTestAvailable

# CMakeビルド関数
function Build-WithCMake {
    Write-ColorOutput Yellow "Building with CMake..."
    
    Set-Location $BuildDir
    
    # CMake設定
    $cmake_cmd = "cmake"
    $cmake_args = @("..", "-G", "Visual Studio 16 2019", "-A", "x64")
    
    if ($env:VCPKG_ROOT) {
        $cmake_args += "-DCMAKE_TOOLCHAIN_FILE=$env:VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake"
    }
    
    Write-Output "Running: $cmake_cmd $cmake_args"
    & $cmake_cmd @cmake_args
    
    if ($LASTEXITCODE -ne 0) {
        Write-ColorOutput Red "CMake configuration failed"
        Set-Location $TestDir
        return $false
    }
    
    # ビルド実行
    Write-Output "Building tests..."
    & cmake --build . --config Debug
    
    $build_success = ($LASTEXITCODE -eq 0)
    Set-Location $TestDir
    return $build_success
}

# Makefileビルド関数（MinGW/MSYS2環境）
function Build-WithMake {
    Write-ColorOutput Yellow "Building with Make (MinGW/MSYS2)..."
    
    try {
        & make --version 2>$null | Out-Null
        if ($LASTEXITCODE -ne 0) {
            Write-ColorOutput Red "Make not found. Please install MinGW or MSYS2."
            return $false
        }
    } catch {
        Write-ColorOutput Red "Make not found. Please install MinGW or MSYS2."
        return $false
    }
    
    Set-Location $TestDir
    & make clean
    & make all
    
    $build_success = ($LASTEXITCODE -eq 0)
    return $build_success
}

# テスト実行関数
function Run-Tests {
    param([string]$Type, [string]$Case, [bool]$VerboseOutput)
    
    $test_executable = ""
    
    if ($UseCMake -and (Test-Path (Join-Path $BuildDir "Debug\striker_tests.exe"))) {
        $test_executable = Join-Path $BuildDir "Debug\striker_tests.exe"
    } elseif (Test-Path (Join-Path $BuildDir "striker_tests.exe")) {
        $test_executable = Join-Path $BuildDir "striker_tests.exe"
    } else {
        Write-ColorOutput Red "Test executable not found. Build may have failed."
        return $false
    }
    
    Write-ColorOutput Green "Running tests: $test_executable"
    Write-Output ""
    
    $test_args = @()
    
    # テストタイプ別フィルタ
    switch ($Type.ToLower()) {
        "unit" {
            $test_args += "--gtest_filter=*Test.*"
            Write-ColorOutput Yellow "Running Unit Tests Only"
        }
        "integration" {
            $test_args += "--gtest_filter=IntegrationTest.*"
            Write-ColorOutput Yellow "Running Integration Tests Only"
        }
        "all" {
            Write-ColorOutput Yellow "Running All Tests"
        }
    }
    
    # 特定テストケース指定
    if ($Case) {
        $test_args += "--gtest_filter=$Case"
        Write-ColorOutput Yellow "Running Test Case: $Case"
    }
    
    # 詳細出力
    if ($VerboseOutput) {
        $test_args += "--gtest_print_time=1"
        $test_args += "--gtest_color=yes"
    }
    
    # テスト実行
    Write-ColorOutput Cyan "===================="
    Write-ColorOutput Cyan "Test Execution"
    Write-ColorOutput Cyan "===================="
    
    & $test_executable @test_args
    $test_result = $LASTEXITCODE
    
    Write-Output ""
    if ($test_result -eq 0) {
        Write-ColorOutput Green "All tests passed!"
    } else {
        Write-ColorOutput Red "Some tests failed. Exit code: $test_result"
    }
    
    return ($test_result -eq 0)
}

# メイン実行フロー
Write-ColorOutput Yellow "Starting test process..."

# Google Test確認
if (-not $GTestAvailable) {
    Write-ColorOutput Red "Google Test framework not available. Cannot run tests."
    exit 1
}

# ビルドのみの場合
if ($TestType.ToLower() -eq "build") {
    Write-ColorOutput Yellow "Build only mode"
    if ($UseCMake) {
        $build_success = Build-WithCMake
    } else {
        $build_success = Build-WithMake
    }
    
    if ($build_success) {
        Write-ColorOutput Green "Build completed successfully"
        exit 0
    } else {
        Write-ColorOutput Red "Build failed"
        exit 1
    }
}

# ビルド実行
Write-ColorOutput Yellow "Building test suite..."
if ($UseCMake) {
    $build_success = Build-WithCMake
} else {
    $build_success = Build-WithMake
}

if (-not $build_success) {
    Write-ColorOutput Red "Build failed. Cannot run tests."
    exit 1
}

# テスト実行
$test_success = Run-Tests -Type $TestType -Case $TestCase -VerboseOutput $Verbose

# カバレッジレポート生成
if ($Coverage -and $test_success) {
    Write-ColorOutput Yellow "Generating coverage report..."
    if (Get-Command gcov -ErrorAction SilentlyContinue) {
        Set-Location $TestDir
        & make coverage
    } else {
        Write-ColorOutput Yellow "gcov not found. Skipping coverage report."
    }
}

# 結果表示
Write-Output ""
Write-ColorOutput Cyan "===================="
Write-ColorOutput Cyan "Test Summary"
Write-ColorOutput Cyan "===================="

if ($build_success -and $test_success) {
    Write-ColorOutput Green "✓ Build: SUCCESS"
    Write-ColorOutput Green "✓ Tests: SUCCESS"
    Write-Output ""
    Write-ColorOutput Green "Strike Gundam test suite completed successfully!"
    exit 0
} else {
    if (-not $build_success) {
        Write-ColorOutput Red "✗ Build: FAILED"
    } else {
        Write-ColorOutput Green "✓ Build: SUCCESS"
    }
    
    if (-not $test_success) {
        Write-ColorOutput Red "✗ Tests: FAILED"
    } else {
        Write-ColorOutput Green "✓ Tests: SUCCESS"
    }
    
    Write-Output ""
    Write-ColorOutput Red "Strike Gundam test suite failed!"
    exit 1
}