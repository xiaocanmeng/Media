import gobject
gobject.threads_init()
import gst
from gi.repository import Gtk
import sys
import os
from audio_video import AVDemo, create_decodebin