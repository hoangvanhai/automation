#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T11:03:55
#
#-------------------------------------------------

QT       += core gui sql serialport network gui-private  widgets #must use "gui-private" for some header files

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = automation
TEMPLATE = app

CONFIG(release, debug|release) {
    DESTDIR = .
    OBJECTS_DIR = .obj
    MOC_DIR = .moc
    RCC_DIR = .rcc
    UI_DIR = .ui
}

DEFINES +=open_safe=open
DEFINES +=char_safe=char
DEFINES +=sprintf_safe=sprintf
DEFINES +=memcpy_safe=memcpy
DEFINES +=setstate_safe=setstate

win32 {
    # To build for various target system, need to change
    # config here
#    CONFIG += TARGET_PLATFORM_x86
    CONFIG += TARGET_PLATFORM_x64
    TARGET_PLATFORM_x64 {
        message(BUILD for x64!)
        INCLUDEPATH +=   $$PWD\openssl\OpenSSL-Win64\include
        QMAKE_LIBDIR +=  $$PWD\openssl\OpenSSL-Win64\lib \
                         $$PWD\protobuf\lib64 \
                         $$PWD\network\pcap\Lib64
    } else:TARGET_PLATFORM_x86 {
        message(BUILD for x86!)
        INCLUDEPATH += $$PWD\openssl\OpenSSL-Win32\include
        QMAKE_LIBDIR +=  $$PWD\openssl\OpenSSL-Win32\lib \
                         $$PWD\protobuf\lib32 \
                         $$PWD\network\pcap\Lib32
    } else {
        message("Fatal error, must select least one target type!")
    }

    INCLUDEPATH +=  $$PWD\lib \
                    $$PWD\protobuf\include \
                    $$PWD\ui \
                    $$PWD\network\pcap\Include \
                    $$PWD\marble

    QMAKE_LIBDIR += $$PWD\marble\lib

    LIBS += -llibprotobuf -llibssl -llibcrypto -lmarblewidget-qt5

    DEFINES += WIN32_LEAN_AND_MEAN  # exclude some APIs Cryptography, DDE, RPC, Shell ...
    DEFINES -= UNICODE              # used for serial port opening with WINAPI
    DEFINES += UDT_EXPORTS          # UDT lib
}

unix{
    CONFIG += c++11
    INCLUDEPATH +=  $$PWD/protobuf/include \
                    $$PWD/lib \
                    $$PWD/ui

    QMAKE_LIBDIR += $$PWD/protobuf/lib

    LIBS += -lmarblewidget-qt5 -ldl -lprotobuf -lssl -lcrypto
}

DEFINES += XLSX_NO_LIB
INCLUDEPATH += $$PWD/protocol \
                $$PWD/database

SOURCES +=  main.cpp\
    ui/maindialog.cpp \
    isc/fifo.cpp \
    isc/layer1.cpp \
    isc/layer2.cpp \
    isc/timer.cpp \
    isc/utils.cpp \
    lib/cli/Console.cpp \
#    lib/cli/ProgressBar.cpp \
#    lib/codec/G729.cpp \
#    lib/codec/GSM.cpp \
#    lib/codec/ULaw.cpp \
#    lib/communication/dhcp/DHCPClient.cpp \
#    lib/communication/protocol/packet/HDLCPacket.cpp \
#    lib/communication/protocol/GoBackN.cpp \
    lib/communication/protocol/SerialFraming.cpp \
    lib/communication/protocol/StackOfLayer.cpp \
    lib/communication/protocol/StreamFraming.cpp \
    lib/communication/socket/ethernet/EthernetSocket.cpp \
    lib/communication/socket/ethernet/EthernetSocket_LinuxMMap.cpp \
    lib/communication/socket/ethernet/EthernetSocket_WinPcap.cpp \
    lib/communication/socket/serialport/SerialPort_Linux.cpp \
    lib/communication/socket/serialport/SerialPort_Win.cpp \
    lib/communication/socket/serialport/SerialSocket.cpp \
    lib/communication/socket/ssl/SSLClient.cpp \
    lib/communication/socket/ssl/SSLServer.cpp \
    lib/communication/socket/tap/TAPSocket.cpp \
    lib/communication/socket/tcp/TCPClient.cpp \
    lib/communication/socket/tcp/TCPServer.cpp \
    lib/communication/socket/tcp/TCPSocket.cpp \
    lib/communication/socket/udp/UDPSocket.cpp \
    lib/communication/socket/ISocket.cpp \
    lib/communication/socket/SocketUtils.cpp \
    lib/container/RingBuffer.cpp \
    lib/dll/DynamicLinkLibrary.cpp \
    lib/error/Error.cpp \
    lib/hash/Base64.cpp \
    lib/hash/MD5.cpp \
    lib/ini/INI.cpp \
    lib/passwd/PasswordManager.cpp \
    lib/rand/Random.cpp \
    lib/safe/Safe.cpp \
    Debugger.cpp \
    isc/crc8.c \
    ui/configuration.cpp \
    ui/testsuite.cpp \
    ui/slidingstackedwidget.cpp \
    ui/testing/testifrf.cpp \
    ui/testing/testsensor.cpp \
    ui/testing/testsystem.cpp \
    network/secureclient.cpp \
    network/controller.cpp \
    csv/csvfile.cpp \
    network/stream.cpp \
    xlsx/xlsxabstractooxmlfile.cpp \
    xlsx/xlsxabstractsheet.cpp \
    xlsx/xlsxcell.cpp \
    xlsx/xlsxcellformula.cpp \
    xlsx/xlsxcellrange.cpp \
    xlsx/xlsxcellreference.cpp \
    xlsx/xlsxchart.cpp \
    xlsx/xlsxchartsheet.cpp \
    xlsx/xlsxcolor.cpp \
    xlsx/xlsxconditionalformatting.cpp \
    xlsx/xlsxcontenttypes.cpp \
    xlsx/xlsxdatavalidation.cpp \
    xlsx/xlsxdocpropsapp.cpp \
    xlsx/xlsxdocpropscore.cpp \
    xlsx/xlsxdocument.cpp \
    xlsx/xlsxdrawing.cpp \
    xlsx/xlsxdrawinganchor.cpp \
    xlsx/xlsxformat.cpp \
    xlsx/xlsxmediafile.cpp \
    xlsx/xlsxnumformatparser.cpp \
    xlsx/xlsxrelationships.cpp \
    xlsx/xlsxrichstring.cpp \
    xlsx/xlsxsharedstrings.cpp \
    xlsx/xlsxsimpleooxmlfile.cpp \
    xlsx/xlsxstyles.cpp \
    xlsx/xlsxtheme.cpp \
    xlsx/xlsxutility.cpp \
    xlsx/xlsxworkbook.cpp \
    xlsx/xlsxworksheet.cpp \
    xlsx/xlsxzipreader.cpp \
    xlsx/xlsxzipwriter.cpp \
    lib/aes/crypto.cpp \
#    udt/api.cpp \
#    udt/buffer.cpp \
#    udt/cache.cpp \
#    udt/ccc.cpp \
#    udt/channel.cpp \
#    udt/common.cpp \
#    udt/core.cpp \
#    udt/epoll.cpp \
#    udt/list.cpp \
#    udt/packet.cpp \
#    udt/queue.cpp \
#    udt/window.cpp \
#    udt/udt_md5.cpp \
#    network/datastream.cpp \
    protocol/client_msg/automation/auto_add.pb.cc \
    protocol/client_msg/automation/auto_remove.pb.cc \
    protocol/client_msg/calibration/table.pb.cc \
    protocol/client_msg/classification/class_cancel.pb.cc \
    protocol/client_msg/classification/class_request.pb.cc \
    protocol/client_msg/classification/class_response.pb.cc \
    protocol/client_msg/classification/class_statistic.pb.cc \
    protocol/client_msg/configuration/mission.pb.cc \
    protocol/client_msg/configuration/noisefloor.pb.cc \
    protocol/client_msg/configuration/online.pb.cc \
    protocol/client_msg/configuration/signalcalc.pb.cc \
    protocol/client_msg/connection/authentication.pb.cc \
    protocol/client_msg/connection/data_channel.pb.cc \
    protocol/client_msg/connection/pingpong.pb.cc \
    protocol/client_msg/demodulation/control.pb.cc \
    protocol/client_msg/geolocation/geo_cancel.pb.cc \
    protocol/client_msg/geolocation/geo_request.pb.cc \
    protocol/client_msg/geolocation/geo_response.pb.cc \
    protocol/client_msg/geolocation/geo_statistic.pb.cc \
    protocol/client_msg/geolocation/geo_status.pb.cc \
    protocol/client_msg/recording/record_cancel.pb.cc \
    protocol/client_msg/recording/record_query.pb.cc \
    protocol/client_msg/recording/record_request.pb.cc \
    protocol/client_msg/recording/record_statistic.pb.cc \
    protocol/client_msg/recording/record_status.pb.cc \
    protocol/client_msg/sensor/gain.pb.cc \
    protocol/client_msg/sensor/local.pb.cc \
    protocol/client_msg/sensor/reset.pb.cc \
    protocol/client_msg/sensor/sensor_add.pb.cc \
    protocol/client_msg/sensor/sensor_query.pb.cc \
    protocol/client_msg/sensor/sensor_remove.pb.cc \
    protocol/client_msg/sensor/update.pb.cc \
    protocol/client_msg/server/clear.pb.cc \
    protocol/client_msg/server/operation.pb.cc \
    protocol/client_msg/server/turnoff.pb.cc \
    protocol/client_msg/signal/async.pb.cc \
    protocol/client_msg/signal/signal_query.pb.cc \
    protocol/client_msg/test/sensor_configuration.pb.cc \
    protocol/client_msg/zoom/zoom_request.pb.cc \
    protocol/client_msg/common.pb.cc \
    protocol/client_msg/msg.pb.cc \
    ui/foldwidget.cpp \
    network/instrument/agilent5182.cpp \
    network/instrument/spectrumfsv.cpp \
    ui/program/flashfpga.cpp \
    ui/program/common/GeneralLib/QRingBuffer.cpp \
    ui/program/common/TransRSP/TransRSPL1.cpp \
    ui/program/common/TransRSP/TransRSPL2.cpp \
    ui/program/tcp/TcpProgItem.cpp \
    ui/program/tcp/TcpProgWorker.cpp \
    ui/program/common/convert.c \
    ui/program/common/CRC4.c \
    ui/program/common/hex.c \
    ui/program/common/vrec.c \
    ui/program/common/VrecEncode.c \
    ui/testing/testfpga.cpp \
    network/fpga.cpp \
    ui/testing/testbase.cpp \
    network/transceiver.cpp \
    ui/calibsensor.cpp \
    network/ethertrans.cpp \
    ui/mapview.cpp \
    ui/map/mapwidget.cpp \
    ui/map/drawlayer1.cpp \
    ui/configuration/uiconfig.cpp \
    ui/configuration/pugixml.cpp \
    ui/testing/testtracker.cpp \
    ui/testing/testgpsdo.cpp \
    ui/testing/testctrlpt.cpp \
    database/databaseconnection.cpp \
    database/dataobject.cpp


HEADERS  += ui/maindialog.h \
    isc/crc8.h \
    isc/fifo.h \
    isc/iscconfig.h \
    isc/layer1.h \
    isc/layer2.h \
    isc/timer.h \
    isc/utils.h \
    lib/cli/Console.h \
    lib/cli/ProgressBar.h \
    lib/codec/G729.h \
    lib/codec/GSM.h \
    lib/codec/ICodec.h \
    lib/codec/ULaw.h \
    lib/communication/dhcp/DHCPClient.h \
    lib/communication/dhcp/DHCPProtocol.h \
    lib/communication/protocol/packet/HDLCPacket.h \
    lib/communication/protocol/GoBackN.h \
    lib/communication/protocol/ILayer.h \
    lib/communication/protocol/SerialFraming.h \
    lib/communication/protocol/StackOfLayer.h \
    lib/communication/protocol/StreamFraming.h \
    lib/communication/socket/ethernet/EthernetSocket.h \
    lib/communication/socket/serialport/SerialSocket.h \
    lib/communication/socket/ssl/SSLClient.h \
    lib/communication/socket/ssl/SSLServer.h \
    lib/communication/socket/tap/TAPSocket.h \
    lib/communication/socket/tcp/TCPClient.h \
    lib/communication/socket/tcp/TCPServer.h \
    lib/communication/socket/tcp/TCPSocket.h \
    lib/communication/socket/udp/UDPSocket.h \
    lib/communication/socket/ISocket.h \
    lib/communication/socket/SocketUtils.h \
    lib/container/RingBuffer.h \
    lib/dll/dll_function.h \
    lib/dll/DynamicLinkLibrary.h \
    lib/error/Error.h \
    lib/hash/Base64.h \
    lib/hash/MD5.h \
    lib/ini/INI.h \
    lib/passwd/PasswordManager.h \
    lib/pattern/IChainOfResponsibility.h \
    lib/pattern/IObserver.h \
    lib/pattern/ISingleton.h \
    lib/rand/Random.h \
    lib/safe/Safe.h \
    lib/string/StringUtils.h \
    lib/cppframework.h \
    debug.h \
    Debugger.h \
    ui/configuration.h \
    ui/testsuite.h \
    ui/slidingstackedwidget.h \
    ui/testing/testifrf.h \
    ui/testing/testsensor.h \
    ui/testing/testsystem.h \
    network/secureclient.h \
    network/controller.h \
    csv/csvfile.h \
    network/stream.h \
    xlsx/xlsxabstractooxmlfile.h \
    xlsx/xlsxabstractooxmlfile_p.h \
    xlsx/xlsxabstractsheet.h \
    xlsx/xlsxabstractsheet_p.h \
    xlsx/xlsxcell.h \
    xlsx/xlsxcell_p.h \
    xlsx/xlsxcellformula.h \
    xlsx/xlsxcellformula_p.h \
    xlsx/xlsxcellrange.h \
    xlsx/xlsxcellreference.h \
    xlsx/xlsxchart.h \
    xlsx/xlsxchart_p.h \
    xlsx/xlsxchartsheet.h \
    xlsx/xlsxchartsheet_p.h \
    xlsx/xlsxcolor_p.h \
    xlsx/xlsxconditionalformatting.h \
    xlsx/xlsxconditionalformatting_p.h \
    xlsx/xlsxcontenttypes_p.h \
    xlsx/xlsxdatavalidation.h \
    xlsx/xlsxdatavalidation_p.h \
    xlsx/xlsxdocpropsapp_p.h \
    xlsx/xlsxdocpropscore_p.h \
    xlsx/xlsxdocument.h \
    xlsx/xlsxdocument_p.h \
    xlsx/xlsxdrawing_p.h \
    xlsx/xlsxdrawinganchor_p.h \
    xlsx/xlsxformat.h \
    xlsx/xlsxformat_p.h \
    xlsx/xlsxglobal.h \
    xlsx/xlsxmediafile_p.h \
    xlsx/xlsxnumformatparser_p.h \
    xlsx/xlsxrelationships_p.h \
    xlsx/xlsxrichstring.h \
    xlsx/xlsxrichstring_p.h \
    xlsx/xlsxsharedstrings_p.h \
    xlsx/xlsxsimpleooxmlfile_p.h \
    xlsx/xlsxstyles_p.h \
    xlsx/xlsxtheme_p.h \
    xlsx/xlsxutility_p.h \
    xlsx/xlsxworkbook.h \
    xlsx/xlsxworkbook_p.h \
    xlsx/xlsxworksheet.h \
    xlsx/xlsxworksheet_p.h \
    xlsx/xlsxzipreader_p.h \
    xlsx/xlsxzipwriter_p.h \
    network/dataflowextract.h \
    lib/aes/crypto.h \
    network/devicecontrol.h \
    udt/api.h \
    udt/buffer.h \
    udt/cache.h \
    udt/ccc.h \
    udt/channel.h \
    udt/common.h \
    udt/core.h \
    udt/epoll.h \
    udt/list.h \
    udt/packet.h \
    udt/queue.h \
    udt/udt.h \
    udt/window.h \
    udt/udt_md5.h \
    network/datastream.h \
    protocol/client_msg/automation/auto_add.pb.h \
    protocol/client_msg/automation/auto_remove.pb.h \
    protocol/client_msg/calibration/table.pb.h \
    protocol/client_msg/classification/class_cancel.pb.h \
    protocol/client_msg/classification/class_request.pb.h \
    protocol/client_msg/classification/class_response.pb.h \
    protocol/client_msg/classification/class_statistic.pb.h \
    protocol/client_msg/configuration/mission.pb.h \
    protocol/client_msg/configuration/noisefloor.pb.h \
    protocol/client_msg/configuration/online.pb.h \
    protocol/client_msg/configuration/signalcalc.pb.h \
    protocol/client_msg/connection/authentication.pb.h \
    protocol/client_msg/connection/data_channel.pb.h \
    protocol/client_msg/connection/pingpong.pb.h \
    protocol/client_msg/demodulation/control.pb.h \
    protocol/client_msg/geolocation/geo_cancel.pb.h \
    protocol/client_msg/geolocation/geo_request.pb.h \
    protocol/client_msg/geolocation/geo_response.pb.h \
    protocol/client_msg/geolocation/geo_statistic.pb.h \
    protocol/client_msg/geolocation/geo_status.pb.h \
    protocol/client_msg/recording/record_cancel.pb.h \
    protocol/client_msg/recording/record_query.pb.h \
    protocol/client_msg/recording/record_request.pb.h \
    protocol/client_msg/recording/record_statistic.pb.h \
    protocol/client_msg/recording/record_status.pb.h \
    protocol/client_msg/sensor/gain.pb.h \
    protocol/client_msg/sensor/local.pb.h \
    protocol/client_msg/sensor/reset.pb.h \
    protocol/client_msg/sensor/sensor_add.pb.h \
    protocol/client_msg/sensor/sensor_query.pb.h \
    protocol/client_msg/sensor/sensor_remove.pb.h \
    protocol/client_msg/sensor/update.pb.h \
    protocol/client_msg/server/clear.pb.h \
    protocol/client_msg/server/operation.pb.h \
    protocol/client_msg/server/turnoff.pb.h \
    protocol/client_msg/signal/async.pb.h \
    protocol/client_msg/signal/signal_query.pb.h \
    protocol/client_msg/test/sensor_configuration.pb.h \
    protocol/client_msg/zoom/zoom_request.pb.h \
    protocol/client_msg/common.pb.h \
    protocol/client_msg/msg.pb.h \
    ui/testconfig.h \
    ui/foldwidget.h \
    network/instrument/agilent5182.h \
    network/instrument/spectrumfsv.h \
    ui/program/flashfpga.h \
    ui/program/common/TransRSP/TransRSPCommon.h \
    ui/program/common/TransRSP/TransRSPL1.h \
    ui/program/common/TransRSP/TransRSPL2.h \
    ui/program/tcp/TcpProgItem.h \
    ui/program/tcp/TcpProgWorker.h \
    ui/program/common/GeneralLib/QRingBuffer.h \
    ui/testing/testfpga.h \
    network/fpga.h \
    ui/testing/testbase.h \
    network/transceiver.h \
    ui/calibsensor.h \
    network/ethertrans.h \
    ui/mapview.h \
    ui/map/mapwidget.h \
    ui/map/drawlayer1.h \
    ui/configuration/uiconfig.h \
    ui/configuration/pugiconfig.hpp \
    ui/configuration/pugixml.hpp \
    ui/testing/testtracker.h \
    ui/testing/testgpsdo.h \
    ui/testing/testctrlpt.h \
    database/databaseconnection.h \
    database/dataobject.h \
    database/macro.h \
    database/objecttable.h \
    database/type_name.h




RESOURCES += \
    ui/img.qrc

DISTFILES += \
    note/pojectnode



