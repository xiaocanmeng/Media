//GStreamer concepts
#include <gst/gst.h>
#include <stdio.h>
#include "log.h"
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif
#include <iostream>
#include "../inc/utility.hpp"


void parseMessage(GstMessage *msg)
{
  InFunLOG();
  /* Parse message */
  if (msg != NULL)
  {
    GError *err{nullptr};
    gchar *debug_info{nullptr};

    switch (GST_MESSAGE_TYPE(msg))
    {
    case GST_MESSAGE_ERROR:
      gst_message_parse_error(msg, &err, &debug_info);
      g_printerr("Error received from element %s: %s\n",
                 GST_OBJECT_NAME(msg->src), err->message);
      g_printerr("Debugging information: %s\n",
                 debug_info ? debug_info : "none");
      g_clear_error(&err);
      g_free(debug_info);
      break;
    case GST_MESSAGE_EOS:
      g_print("End-Of-Stream reached.\n");
      break;
    default:
      /* We should not reach here because we only asked for ERRORs and EOS */
      g_printerr("Unexpected message received.\n");
      break;
    }
    gst_message_unref(msg);
  }
  OutFunLOG();
}

int32_t tutorial_main_2(int32_t argc, char *argv[])
{
  InFunLOG();
  GstElement *pipeline{nullptr};
  GstElement *source{nullptr};
  GstElement *sink{nullptr};
  GstElement *vertigotv{nullptr};
  GstBus *bus{nullptr};
  GstMessage *msg{nullptr};
  GstStateChangeReturn ret;

  /* Initialize GStreamer */
  gst_init(&argc, &argv);

  /* Create the elements */
  source = gst_element_factory_make("videotestsrc", "source");
  vertigotv = gst_element_factory_make("vertigotv", "vertigotv");
  sink = gst_element_factory_make("autovideosink", "sink");

  /* Create the empty pipeline */
  pipeline = gst_pipeline_new("test-pipeline");
  
  if (!isNULL(pipeline, source, vertigotv, sink))
  {
    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(pipeline), source, vertigotv, sink, NULL);
    if(linkElements(source, vertigotv, sink))
    {
      /* Modify the source's properties */
      g_object_set(source, "pattern", 0, NULL);

      /* Start playing */
      ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
      if (ret != GST_STATE_CHANGE_FAILURE)
      {
        /* Wait until error or EOS */
        bus = gst_element_get_bus(pipeline);
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                         static_cast<GstMessageType>(GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
        /* Parse message */
        parseMessage(msg);
        /* Free resources */
        gst_object_unref(bus);
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_object_unref(pipeline);
      }
      else
      {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(pipeline);
      }
    }
    else
    {
       std::cout<<"Elements could not be linked."<<__LINE__<<std::endl;
       gst_object_unref(pipeline);
    }
  }
  else
  {
    g_printerr("Not all elements could be created.\n");
  }
  OutFunLOG();
  return 0;
}
