// Dynamic pipelines
#include <gst/gst.h>
#include "sample.h"
#include "utility.hpp"
/*******************************************************************************
* @brief      {brief}
* 
* @param      [in]    new_pad_caps
* @param      [in]    sink_pad
* 
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
void Sample::exit(GstCaps *new_pad_caps,GstPad *sink_pad)
{
   /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
  {
    gst_caps_unref (new_pad_caps);
  }

  /* Unreference the audiosink pad */
  gst_object_unref (sink_pad);
}
/*******************************************************************************
* @brief      {brief}
* 
* @param      [in]    src
* @param      [in]    new_pad
* @param      [in]    data
* @param      [in]    pad_type
* @param      [in]    prefix
* 
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
void Sample::pad_added_handler(GstElement *src, GstPad *new_pad, CustomData *data,GstPad *sink_pad,const gchar * prefix)
{
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;
  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));
  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) 
  {
    g_print ("We are already linked. Ignoring.\n");
    exit(new_pad_caps,sink_pad);
  }
  else
  {
    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name (new_pad_struct);
    if (!g_str_has_prefix (new_pad_type, prefix)) 
    {
      g_print ("It has type '%s' which is not raw video. Ignoring.\n", new_pad_type);
      exit(new_pad_caps,sink_pad);
    }
    else
    {
      /* Attempt the link */
      ret = gst_pad_link (new_pad, sink_pad);
      if (GST_PAD_LINK_FAILED (ret)) 
      {
        g_print ("Type is '%s' but link failed.\n", new_pad_type);
      } 
      else 
      {
        g_print ("Link succeeded (type '%s').\n", new_pad_type);
      }
    }
  }
}
/*******************************************************************************
* @brief      This function will be called by the pad-added signal 
* 
* 
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
void Sample::audio_pad_added_handler (GstElement *src, GstPad *new_pad, CustomData *data) 
{
  GstPad *sink_pad = gst_element_get_static_pad (data->audioconvert, "sink");
  pad_added_handler(src,new_pad,data,sink_pad,"audio/x-raw");
}
/*******************************************************************************
* @brief      {brief}
* 
* @param      [in]    src
* @param      [in]    new_pad
* @param      [in]    data
* 
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
void Sample::video_pad_added_handler (GstElement *src, GstPad *new_pad, CustomData *data) 
{
  GstPad *sink_pad = gst_element_get_static_pad (data->videoconvert, "sink");
  pad_added_handler(src,new_pad,data,sink_pad,"video/x-raw");
}
/*******************************************************************************
* @brief      {brief}
* 
* @param      [in]    bus
* 
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
void Sample::parseMessage(GstBus *bus)
{
  GstMessage *msg;
  bool terminate = false;
  do {
    msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
        static_cast<GstMessageType>(GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS));
    /* Parse message */
    if (msg != NULL) {
      GError *err;
      gchar *debug_info;

      switch (GST_MESSAGE_TYPE (msg)) {
        case GST_MESSAGE_ERROR:
          gst_message_parse_error (msg, &err, &debug_info);
          g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
          g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
          g_clear_error (&err);
          g_free (debug_info);
          terminate = true;
          break;
        case GST_MESSAGE_EOS:
          g_print ("End-Of-Stream reached.\n");
          terminate = true;
          break;
        case GST_MESSAGE_STATE_CHANGED:
          /* We are only interested in state-changed messages from the pipeline */
          if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data.pipeline)) {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
            g_print ("Pipeline state changed from %s to %s:\n",
                gst_element_state_get_name (old_state), gst_element_state_get_name (new_state));
          }
          break;
        default:
          /* We should not reach here */
          g_printerr ("Unexpected message received.\n");
          break;
      }
      gst_message_unref (msg);
    }
  } while (!terminate);
}


/*******************************************************************************
* @brief      {brief}
* 
* @param      [in]    argc
* @param      [in]    argv
* 
* @retval     int32_t
* 
* @author     XIAOCANMENG
* 
* @par        revision history:
*              - 000000 : 2024-01-02 : XIAOCANMENG    : New regulations made
* 
* @par        Sequence diagram:
* @image      {name}.png
*******************************************************************************/
int32_t Sample::tutorial_main_3(int32_t argc, char *argv[]) 
{
  CustomData data;
  GstBus *bus;
  GstStateChangeReturn ret;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  /* Create the elements */
  data.source = gst_element_factory_make ("uridecodebin", "source");
  data.audioconvert = gst_element_factory_make ("audioconvert", "audioconvert");
  data.resample = gst_element_factory_make ("audioresample", "resample");
  data.audiosink = gst_element_factory_make ("autoaudiosink", "audiosink");
  data.videoconvert = gst_element_factory_make ("videoconvert", "videoconvert");
  data.videosink = gst_element_factory_make ("autovideosink", "videosink");

  /* Create the empty pipeline */
  data.pipeline = gst_pipeline_new ("test-pipeline");

  // if (isNULL(data.pipeline,data.source,data.audioconvert,data.resample,data.audiosink,data.videoconvert, data.videosink)) 
  if (isNULL(data.pipeline,data.source,data.videoconvert, data.videosink)) 
  {
    g_printerr ("Not all elements could be created.\n");
  }
  else
  {
    /* Build the pipeline. Note that we are NOT linking the source at this
       point. We will do it later. */
    gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.audioconvert, data.resample, data.audiosink, data.videosink, data.videoconvert, NULL);
    // gst_bin_add_many(GST_BIN(data.pipeline), data.source, data.videoconvert, data.videosink, NULL);
    if (!gst_element_link_many(data.audioconvert, data.resample, data.audiosink, NULL) ||
         !gst_element_link_many(data.videoconvert, data.videosink, NULL))
    {
      g_printerr("Elements could not be linked.\n");
      gst_object_unref(data.pipeline);
    }
    else
    {
      /* Set the URI to play */
      g_object_set(data.source, "uri", "https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm", NULL);
      /* Connect to the pad-added signal */
      g_signal_connect(data.source, "pad-added", G_CALLBACK(audio_pad_added_handler), &data);
      g_signal_connect(data.source, "pad-added", G_CALLBACK(video_pad_added_handler), &data);
      /* Start playing */
      ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
      if (ret == GST_STATE_CHANGE_FAILURE)
      {
        g_printerr("Unable to set the pipeline to the playing state.\n");
        gst_object_unref(data.pipeline);
      }
      else
      {
        /* Listen to the bus */
        bus = gst_element_get_bus(data.pipeline);
        /* Parse message */
        parseMessage(bus);
        /* Free resources */
        gst_object_unref(bus);
        gst_element_set_state(data.pipeline, GST_STATE_NULL);
        gst_object_unref(data.pipeline);
      }
    }
  }
  return 0;
}

