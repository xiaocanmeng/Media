#include <iostream>

/* Structure to contain all our information, so we can pass it to callbacks */
struct CustomData 
{
  GstElement *pipeline;
  GstElement *source;
  GstElement *resample;
  GstElement *audioconvert;
  GstElement *audiosink;
  GstElement *videoconvert;
  GstElement *videosink;
};


/* C++ refactoring tutorial*/
class Sample
{
private:
    CustomData data;
    /* Handler for the pad-added signal */
    static void audio_pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
    static void video_pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
    void parseMessage(GstBus *bus);
    static void exit(GstCaps *new_pad_caps,GstPad *sink_pad);
    static void pad_added_handler(GstElement *src, GstPad *new_pad, CustomData *data,GstPad *sink_pad,const gchar * prefix);
public:    
    int32_t tutorial_main_3(int argc, char *argv[]);
};