#include <gst/gst.h>
static void
cb_new_pad (GstElement *element,
	    GstPad     *pad,
	    gpointer    data)
{
	GstPad *sinkpad;
	GstElement *depayload = (GstElement *) data;

	/* We can now link this pad with the vorbis-decoder sink pad */
	g_print ("Dynamic pad created, linking source/depayload\n");

	sinkpad = gst_element_get_static_pad (depayload, "sink");

	gst_pad_link (pad, sinkpad);

	gst_object_unref (sinkpad);
}
  


int main(int argc, char *argv[]) {

	GstElement *pipeline, *source, *decoder, *depay, *source2, *videosink, *decoder2, *depay2, *videosink2, *source3, *decoder3, *depay3, *videosink3, *source4, *decoder4, *depay4, *videosink4/*, *queue, *queue2, *queue3, *queue4, *demux, *demux2, *demux3, *demux4*/;
	GstBus *bus;
	GstMessage *msg;
	GMainLoop *loop;
	gchar *camip;
	gint latency = 40;
	camip="rtsp://192.168.10.4/h264.sdp";
	/* Initialize GStreamer */
	gst_init (&argc, &argv);
	
	
	
	videosink = gst_element_factory_make("autovideosink", "sink");
	source = gst_element_factory_make("rtspsrc","src_1");
	decoder = gst_element_factory_make("avdec_h264", "h264decoder");	
	depay = gst_element_factory_make("rtph264depay", "depayload");	
	//queue = gst_element_factory_make("queue", "q1");
	//demux = gst_element_factory_make("uvch264mjpgdemux","demux");
	
	
	videosink2 = gst_element_factory_make("autovideosink", "sink2");
	source2 = gst_element_factory_make("rtspsrc","src_2");
	decoder2 = gst_element_factory_make("avdec_h264", "h264decoder2");	
	depay2 = gst_element_factory_make("rtph264depay", "depayload2");	
	//queue2 = gst_element_factory_make("queue", "q2");
	//demux2 = gst_element_factory_make("uvch264mjpgdemux","demux2");
	
	videosink3 = gst_element_factory_make("autovideosink", "sink3");
	source3 = gst_element_factory_make("rtspsrc","src_3");
	decoder3 = gst_element_factory_make("avdec_h264", "jpgdecoder3");	
	depay3 = gst_element_factory_make("rtph264depay", "depayload3");	
	//queue3 = gst_element_factory_make("queue", "q3");
	//demux3 = gst_element_factory_make("uvch264mjpgdemux","demux3");

	videosink4 = gst_element_factory_make("autovideosink", "sink4");
	source4 = gst_element_factory_make("rtspsrc","src_4");
	decoder4 = gst_element_factory_make("avdec_h264", "h264decoder4");	
	depay4 = gst_element_factory_make("rtph264depay", "depayload4");	
	//queue4 = gst_element_factory_make("queue", "q4");	
	//demux4 = gst_element_factory_make("uvch264mjpgdemux","demux4");

	pipeline = gst_pipeline_new("the-pipeline");

	/*
speed-preset        : Preset name for speed/quality tradeoff options (can affect decode compatibility - impose restrictions separately for your target decoder)
                        flags: readable, writable
                        Enum "GstX264EncPreset" Default: 6, "medium"
                           (0): None             - No preset
                           (1): ultrafast        - ultrafast
                           (2): superfast        - superfast
                           (3): veryfast         - veryfast
                           (4): faster           - faster
                           (5): fast             - fast
                           (6): medium           - medium
                           (7): slow             - slow
                           (8): slower           - slower
                           (9): veryslow         - veryslow
                           (10): placebo          - placebo
	*/
	
	if (!videosink || !source || !decoder|| !depay || !source2 || !decoder2 || !depay2 || !videosink2 || !source3 || !decoder3 || !depay3 || !videosink3 || !source4 || !decoder4 || !depay4 || !videosink4) {
	    g_printerr ("One element could not be created. Exiting.\n");
	    return -1;
	}
	g_object_set(G_OBJECT(source), "location", camip, "latency", latency, "protocols", 0x00000001, NULL);
	g_object_set(G_OBJECT(source2), "location", camip, "latency", latency,  "protocols", 0x00000001,  NULL);
	g_object_set(G_OBJECT(source3), "location", camip, "latency", latency, "protocols", 0x00000001,   NULL);
	g_object_set(G_OBJECT(source4), "location", camip, "latency", latency, "protocols", 0x00000001,   NULL);
	/*g_object_set(decoder, "max-errors", "-1", NULL);
	g_object_set(decoder2, "max-errors", "-1", NULL);
	g_object_set(decoder3, "max-errors", "-1", NULL);
	g_object_set(decoder4, "max-errors", "-1", NULL);*/
	//g_object_set(demux, "single-stream", GTRUE, NULL);
	/* ADD TO A BIN */
	gst_bin_add_many (GST_BIN(pipeline), source, decoder, depay, videosink, NULL);
	gst_bin_add_many (GST_BIN(pipeline), source2, decoder2, depay2, videosink2, NULL);
	gst_bin_add_many (GST_BIN(pipeline), source3, decoder3, depay3, videosink3, NULL);
	gst_bin_add_many (GST_BIN(pipeline), source4, decoder4, depay4, videosink4, NULL);
	
	/* LINK ELEMENTS */
	if (!(gst_element_link_many(depay, decoder, videosink, NULL)) || 
!(gst_element_link_many(depay2, decoder2, videosink2, NULL)) || 
!(gst_element_link_many(depay3, decoder3, videosink3, NULL)) || 
!(gst_element_link_many(depay4, decoder4, videosink4, NULL))){
	g_print ("Error linking elements");
  	return -1;
	}
	
	/*gst_element_link_pads (source, "src_1", depay, "depayload");
	gst_element_link_pads (source2, "src_2", depay2, "depayload2");
	gst_element_link_pads (source3, "src_3", depay3, "depayload3");
	gst_element_link_pads (source4, "src_4", depay4, "depayload4");
	*/
	 /* listen for newly created pads */
 	g_signal_connect (source, "pad-added", G_CALLBACK (cb_new_pad), depay);	
	g_signal_connect (source2, "pad-added", G_CALLBACK (cb_new_pad), depay2);	
	g_signal_connect (source3, "pad-added", G_CALLBACK (cb_new_pad), depay3);	
	g_signal_connect (source4, "pad-added", G_CALLBACK (cb_new_pad), depay4);	



	gst_element_set_state (pipeline, GST_STATE_PLAYING);
	loop = g_main_loop_new(NULL, FALSE);
	g_main_loop_run(loop);
	/* Wait until error or EOS */
	bus = gst_element_get_bus (pipeline);
	msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* Free resources */
	if (msg != NULL)
	gst_message_unref (msg);
	gst_object_unref (bus);
	gst_element_set_state (pipeline, GST_STATE_NULL);
	gst_object_unref (pipeline);
	g_main_loop_unref (loop);
	return 0;
}
 
