set(BOX2D_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")

set(BOX2D_LIBRARIES "${CMAKE_CURRENT_LIST_DIR}/lib/libbox2d.a")

string(STRIP "${BOX2D_LIBRARIES}" BOX2D_LIBRARIES)