cmake_minimum_required(VERSION 3.20)    # 最低バージョンを指定

project(NovelEngine)    # プロジェクト名を指定

find_package(SDL3 CONFIG REQUIRED)

add_executable(     # 実行ファイルを作る
    NovelEngine     # 実行ファイル名（NovelEngine.exe）
    src/main.cpp    # 使用するソース
    src/Application.cpp
    src/Graphics.cpp
    src/Input.cpp
    src/Scenario.cpp
)

# NovelEngineをC++17としてコンパイル
target_compile_features(
    NovelEngine
    PRIVATE
    cxx_std_17
)

# NovelEngineがSDL3を使用するという指定
target_link_libraries(
    NovelEngine
    PRIVATE
    SDL3::SDL3
)

# ソースコードと実行時文字列をUTF-8として明示
if(MSVC)
    target_compile_options(
        NovelEngine
        PRIVATE
        /utf-8        
    )
endif()

# 指定したターゲットのビルド後にコマンドを実行
add_custom_command(
    TARGET NovelEngine
    POST_BUILD  # NovelEngineのビルドが完了した後に以下を実行（今回は実行ファイルとアセットを同じ出力構造へまとめている）
    COMMAND ${CMAKE_COMMAND} -E copy_directory  # ディレクトリの内容をコピー
        "${CMAKE_SOURCE_DIR}/assets"            # CMakeLists.txtがあるソースディレクトリを表している（NovelEngine/assets）
        "$<TARGET_FILE_DIR:NovelEngine>/assets" # NovelEngineの実行ファイルが生成されるディレクトリ（通常はbuild/Debug/assets）
    COMMENT "Copying assets"
)

