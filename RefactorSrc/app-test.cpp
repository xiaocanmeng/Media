#include <gst/gst.h>
#include <string>
#include <iostream>

int32_t build_pipeline(int32_t argc, char *argv[])
{
    GstElement *pipeline;
    GError *error = NULL;
    gst_init(&argc, &argv);
    std::string m_strPipeline = "filesrc location=/home/dev/work/Media/data/test.mp4 ! qtdemux ! avdec_h264  ! autovideosink";
    pipeline = gst_parse_launch(m_strPipeline.c_str(), &error);
    if (error != NULL)
    {
        printf("Could not construct pipeline: %s", error->message);
        g_clear_error(&error);
    }

    // ...

    return 0;
}