#
# 全リポジトリ共通のcmakeをインクルードします。
# デンソーテン）インテグチームで管理するため、ここに追加しないようにお願い致します。
# Yoctoビルドおよび、YoctoSDKビルド両方の環境でビルド可能なコンフィグレーションを集約しています。
#

# ローカル編集可能な、cmake ファイル
include(${CMAKE_SOURCE_DIR}/cmake/local.cmake)

if(TIER1_NEW_DIRLAYOUT)
    include(${CMAKE_SOURCE_DIR}/cmake/dirlayout/config-dirlayout-dten.cmake)
else()
    include(${CMAKE_SOURCE_DIR}/cmake/dirlayout/config-dirlayout-arene.cmake)
endif()
