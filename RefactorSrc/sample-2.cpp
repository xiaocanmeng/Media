#include <gst/gst.h>
#include <stdio.h>
#include "log.h"
#ifdef __APPLE__
#include <TargetConditionals.h>
#endif
#include <iostream>
#include <tuple>
// Base case: stop recursion when there are no arguments
bool isNULL()
{
  return false;
}

// variadic template
template <typename T, typename... Args>
bool isNULL(T first, Args... args)
{
  if (first != nullptr)
  {
    return isNULL(args...); // recursive call
  }
  else
  {
    return true;
  }
}

// Termination conditions for recursive calls
template <typename GstElement>
bool linkElementsHelper(GstElement *source, GstElement *last)
{
  // Base case: Only two elements, link them directly.
  return gst_element_link(source, last);
}

// Auxiliary structure for recursively linking elements
template <typename First, typename Second, typename... Rest>
bool linkElementsHelper(First *first, Second *second, Rest *...rest)
{
  // Recursive case: Link the adjacent elements and call itself recursively for the rest.
  return gst_element_link(first, second) && linkElementsHelper(second, rest...);
}

// The outermost linkElements function is used to start recursion
template <typename... GstElementTypes>
bool linkElements(GstElementTypes *...elements)
{
  // External interface that calls the helper function.
  return linkElementsHelper(elements...); // Fold Expressions Template
}

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

int tutorial_main_2(int argc, char *argv[])
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
