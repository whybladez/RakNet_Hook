#include "packet_handler.h"

// Packet Handler for hook Incoming packets!

PluginReceiveResult packet_handler::OnReceive(RakPeerInterface* peer, Packet* packet)
{
	if (packet && packet->data[0] == 207)
	{
		return RR_CONTINUE_PROCESSING;
	}

	return RR_CONTINUE_PROCESSING;
}

void raknet_plugin_attacher::attach(RakClientInterface* rakclient, PluginInterface *handler) {
	this->rakclient = rakclient;
	this->handler = handler;

	rakclient->AttachPlugin(handler);
}

raknet_plugin_attacher::~raknet_plugin_attacher() {
	if (handler) {
		rakclient->DetachPlugin(handler);
		delete handler;
	}
}

raknet_plugin_attacher raknet_plugin_attacher_instance;