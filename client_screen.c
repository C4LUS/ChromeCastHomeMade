#include <gst/gst.h>

int main(int argc, char *argv[])
{
    GstElement *pipeline;
    GstBus *bus;
    GstMessage *msg;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    pipeline = gst_parse_launch("gst-launch-1.0 ximagesrc ! videoconvert ! x264enc ! rtph264pay config-interval=1 pt=96 ! udpsink host=10.49.84.136 port=5000", NULL);
    if (!pipeline) {
        g_printerr("Failed to create pipeline\n");
        return -1;
    }

    /* Start playing */
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    /* Wait until error or EOS */
    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
                                     GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if (msg) {
        if (GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
            GError *err;
            gchar *dbg;
            gst_message_parse_error(msg, &err, &dbg);
            g_printerr("Error: %s\nDebug info: %s\n",
                       err->message, dbg ? dbg : "none");
            g_error_free(err);
            g_free(dbg);
        } else {
            g_print("End-Of-Stream reached.\n");
        }
        gst_message_unref(msg);
    }

    /* Cleanup */
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
