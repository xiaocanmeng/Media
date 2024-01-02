#include <iostream>

/* Structure to contain all our information, so we can pass it to callbacks */
struct CustomData {
  GstElement *pipeline;
  GstElement *source;
  GstElement *convert;
  GstElement *resample;
  GstElement *sink;
};


/* C++ refactoring tutorial*/
class Sample
{
private:
    CustomData data;
    /* Handler for the pad-added signal */
    static void pad_added_handler (GstElement *src, GstPad *pad, CustomData *data);
public:    
    int32_t tutorial_main_3(int argc, char *argv[]);
};