cmake_minimum_required(VERSION 3.20)    # 最低バージョンを指定

project(NovelEngine)    # プロジェクト名を指定

add_executable(     # 実行ファイルを作る
    NovelEngine     # 実行ファイル名（NovelEngine.exe）
    src/main.cpp    # 使用するソース
    src/Application.cpp
)