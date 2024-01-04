#include <iostream>

/* Structure to contain all our information, so we can pass it to callbacks */
struct CustomData
{
  // sample-3
  GstElement *pipeline;
  GstElement *source;
  GstElement *resample;
  GstElement *audioconvert;
  GstElement *audiosink;
  GstElement *videoconvert;
  GstElement *videosink;
  // sameple-4
  GstElement *playbin;   /* Our one and only element */
  gboolean playing;      /* Are we in the PLAYING state? */
  gboolean terminate;    /* Should we terminate execution? */
  gboolean seek_enabled; /* Is seeking enabled for this media? */
  gboolean seek_done;    /* Have we performed the seek already? */
  // gint64 duration;       /* How long does this media last, in nanoseconds */
  
  //sample-5
  // GstElement *playbin; /* Our one and only pipeline */
  GtkWidget *sink_widget;         /* The widget where our video will be displayed */
  GtkWidget *slider;              /* Slider widget to keep track of current position */
  GtkWidget *streams_list;        /* Text widget to display info about the streams */
  gulong slider_update_signal_id; /* Signal ID for the slider update signal */

  GstState state;  /* Current state of the pipeline */
  gint64 duration; /* Duration of the clip, in nanoseconds */
};

/* C++ refactoring tutorial*/
class Sample
{
private:
  CustomData data;
  /* Handler for the pad-added signal */
  static void audio_pad_added_handler(GstElement *src, GstPad *pad, CustomData *data);
  static void video_pad_added_handler(GstElement *src, GstPad *pad, CustomData *data);
  void parseMessage(GstBus *bus);
  static void exit(GstCaps *new_pad_caps, GstPad *sink_pad);
  static void pad_added_handler(GstElement *src, GstPad *new_pad, CustomData *data, GstPad *sink_pad, const gchar *prefix);
  static void handle_message(CustomData *data, GstMessage *msg);

public:
  int32_t tutorial_main_3(int32_t argc, char *argv[]);
  int32_t tutorial_main_4(int32_t argc, char *argv[]);
};