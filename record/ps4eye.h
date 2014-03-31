
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>

#include "libusb.h"

using namespace std;

typedef unsigned char uchar;


class ps4eye {

public:
  ps4eye();
  ~ps4eye();

  void init();
  void play();
  void stop();

  ofstream * datadump;
  size_t packet_size;
  uchar * null_packet;

private:

  bool returned;
  bool abort;
  bool controlTransferReturned;

  unsigned long int samplerate;

  libusb_device * dev;
  libusb_context * context;
  libusb_device_handle * handle;

  struct libusb_transfer * control_transfer;
  uchar * control_transfer_buffer;
  uchar * video_in_buffer;
  unsigned long int buffersize;
  unsigned int control_wLength;
  size_t num_packets;

  struct libusb_transfer * video_transfer;

  void firmware_upload();
  void setup_usb();
  void startup_commands();
  void release_usb();
  void resumePlayback();

  void submitAndWait_controlTransfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue,
                                     uint16_t wIndex, uint16_t wLength, uchar *buffer);

  void submit_controlTransfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue,
                              uint16_t wIndex, uint16_t wLength, uchar *buffer);

  static void callback_controlTransfer(struct libusb_transfer * transfer);

  static void debug_callback(struct libusb_transfer * transfer);

  static void callback_videoin(struct libusb_transfer * transfer);

  struct vector<libusb_transfer*> allocate_iso_input_transfers(int num_transfers);
};

