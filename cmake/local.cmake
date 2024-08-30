# 新しいフォルダレイアウト版に対応する場合は、ONにする。
# ON: /opt/dc-ivi-pf
# OFF: /usr
option(TIER1_NEW_DIRLAYOUT "use new directory layout" ON)

include(${CMAKE_SOURCE_DIR}/cmake/Modules/arene.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Modules/dten.cmake)
