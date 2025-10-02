# Strike Gundam Project Test Makefile
# STM32 embedded development with Google Test framework

# コンパイラ設定
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -O0

# ディレクトリ設定
PROJECT_ROOT = ..
SRC_DIR = $(PROJECT_ROOT)/src
TEST_DIR = .
MOCK_DIR = $(TEST_DIR)/mocks
UNIT_TEST_DIR = $(TEST_DIR)/unit
INTEGRATION_TEST_DIR = $(TEST_DIR)/integration
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Google Test設定
GTEST_DIR = /usr/local/include/gtest
GMOCK_DIR = /usr/local/include/gmock
GTEST_LIBS = -lgtest -lgtest_main -lgmock -lgmock_main -lpthread

# インクルードパス
INCLUDES = -I$(SRC_DIR) -I$(MOCK_DIR) -I$(GTEST_DIR) -I$(GMOCK_DIR)

# ソースファイル
MOCK_SOURCES = $(MOCK_DIR)/mock_arduino.cpp
TEST_SOURCES = $(wildcard $(UNIT_TEST_DIR)/*.cpp) \
               $(wildcard $(INTEGRATION_TEST_DIR)/*.cpp)

# オブジェクトファイル
MOCK_OBJECTS = $(patsubst $(MOCK_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MOCK_SOURCES))
TEST_OBJECTS = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(TEST_SOURCES))

# 実行ファイル
TEST_EXECUTABLE = $(BUILD_DIR)/striker_tests

# デフォルトターゲット
all: directories $(TEST_EXECUTABLE)

# ディレクトリ作成
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/unit
	@mkdir -p $(OBJ_DIR)/integration

# テスト実行ファイルのビルド
$(TEST_EXECUTABLE): $(MOCK_OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(GTEST_LIBS) -o $@

# モックオブジェクトファイルのコンパイル
$(OBJ_DIR)/%.o: $(MOCK_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ユニットテストオブジェクトファイルのコンパイル
$(OBJ_DIR)/unit/%.o: $(UNIT_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 統合テストオブジェクトファイルのコンパイル
$(OBJ_DIR)/integration/%.o: $(INTEGRATION_TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# テスト実行
test: $(TEST_EXECUTABLE)
	@echo "===================="
	@echo "Strike Gundam Tests"
	@echo "===================="
	./$(TEST_EXECUTABLE)

# ユニットテストのみ実行
unit-test: $(TEST_EXECUTABLE)
	@echo "===================="
	@echo "Unit Tests Only"
	@echo "===================="
	./$(TEST_EXECUTABLE) --gtest_filter="*Test*"

# 統合テストのみ実行
integration-test: $(TEST_EXECUTABLE)
	@echo "===================="
	@echo "Integration Tests Only"
	@echo "===================="
	./$(TEST_EXECUTABLE) --gtest_filter="IntegrationTest*"

# 詳細なテスト実行（全出力表示）
test-verbose: $(TEST_EXECUTABLE)
	@echo "===================="
	@echo "Verbose Test Output"
	@echo "===================="
	./$(TEST_EXECUTABLE) --gtest_print_time=1 --gtest_color=yes

# 特定のテストケース実行
test-case:
	@echo "Usage: make test-case CASE=TestCaseName"
	@echo "Example: make test-case CASE=StrikeSystemTest.ChangeStrikerTest"
ifdef CASE
	./$(TEST_EXECUTABLE) --gtest_filter="$(CASE)"
endif

# コードカバレッジ（gcovが利用可能な場合）
coverage: clean
	$(MAKE) CXXFLAGS="$(CXXFLAGS) -fprofile-arcs -ftest-coverage" test
	@echo "Generating coverage report..."
	gcov $(TEST_SOURCES) $(MOCK_SOURCES)
	@echo "Coverage files generated: *.gcov"

# メモリチェック（valgrindが利用可能な場合）
memcheck: $(TEST_EXECUTABLE)
	@echo "Running memory check..."
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_EXECUTABLE)

# 静的解析（cppcheckが利用可能な場合）
static-analysis:
	@echo "Running static analysis..."
	cppcheck --enable=all --std=c++11 $(SRC_DIR) $(TEST_DIR)

# クリーンアップ
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.gcov *.gcno *.gcda

# 完全クリーンアップ
distclean: clean
	rm -f test_results.xml
	rm -f coverage.info

# ヘルプ
help:
	@echo "Strike Gundam Test Makefile"
	@echo "=========================="
	@echo "Available targets:"
	@echo "  all              - Build all tests"
	@echo "  test             - Run all tests"
	@echo "  unit-test        - Run unit tests only"
	@echo "  integration-test - Run integration tests only"
	@echo "  test-verbose     - Run tests with verbose output"
	@echo "  test-case        - Run specific test case (use CASE=name)"
	@echo "  coverage         - Generate code coverage report"
	@echo "  memcheck         - Run memory leak detection"
	@echo "  static-analysis  - Run static code analysis"
	@echo "  clean            - Clean build files"
	@echo "  distclean        - Clean all generated files"
	@echo "  help             - Show this help"

# CI/CD用XMLレポート生成
xml-report: $(TEST_EXECUTABLE)
	./$(TEST_EXECUTABLE) --gtest_output=xml:test_results.xml

# 依存関係の明示
.PHONY: all directories test unit-test integration-test test-verbose test-case coverage memcheck static-analysis clean distclean help xml-report

# 自動依存関係生成
-include $(TEST_OBJECTS:.o=.d)
-include $(MOCK_OBJECTS:.o=.d)

# 依存関係ファイル生成ルール
$(OBJ_DIR)/%.d: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MM -MF $@ -MT $(@:.d=.o) $<