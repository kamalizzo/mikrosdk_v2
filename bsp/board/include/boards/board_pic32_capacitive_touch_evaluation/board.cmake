if(${_MSDK_BOARD_NAME_} STREQUAL "PIC32_CAPACITIVE_TOUCH_EVALUATION_BOARD")
    set(BOARD_PATH "include/boards/board_pic32_capacitive_touch_evaluation")
    set(MCU_CARD FALSE)
    set(SHIELD FALSE)
    set(DIP_SOCKET FALSE)
endif()
