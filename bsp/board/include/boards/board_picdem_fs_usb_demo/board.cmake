if(${_MSDK_BOARD_NAME_} STREQUAL "PICDEM_FS_USB_DEMO_BOARD")
    set(BOARD_PATH "include/boards/board_picdem_fs_usb_demo")
    set(MCU_CARD FALSE)
    set(SHIELD FALSE)
endif()
