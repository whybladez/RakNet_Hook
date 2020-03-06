#include "main.h"

// RakHook.cpp for hook Outcoming packets!

bool HookedRakClientInterface::Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )
{
	return pSAMP->getRakClientInterface()->Connect( host, serverPort, clientPort, depreciated, threadSleepTimer );
}

void HookedRakClientInterface::Disconnect( unsigned int blockDuration, unsigned char orderingChannel )
{
	pSAMP->getRakClientInterface()->Disconnect( blockDuration, orderingChannel );
}

void HookedRakClientInterface::InitializeSecurity( const char *privKeyP, const char *privKeyQ )
{
	pSAMP->getRakClientInterface()->InitializeSecurity( privKeyP, privKeyQ );
}

void HookedRakClientInterface::SetPassword( const char *_password )
{
	pSAMP->getRakClientInterface()->SetPassword( _password );
}

bool HookedRakClientInterface::HasPassword( void ) const
{
	return pSAMP->getRakClientInterface()->HasPassword();
}

bool HookedRakClientInterface::Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel)
{
	return pSAMP->getRakClientInterface()->Send(data, length, priority, reliability, orderingChannel);
}

bool HookedRakClientInterface::Send( RakNet::BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	BYTE packetId;
	bitStream->Read(packetId);

	switch (packetId)
	{
		case ID_AIM_SYNC:
		{
			CPed *bLocalPed = reinterpret_cast<CPed *>(getGTAPedFromSAMPPlayerID(pSAMP->getPlayers()->sLocalPlayerID));
			bLocalPed->SetAimFlag(0.0f);
			bLocalPed->SetHeading(0.0f);
		}
		break;

		case ID_PLAYER_SYNC:
		{
			
		}
		break;

		case ID_VEHICLE_SYNC:
		{
			
		}
		break;

		case ID_BULLET_SYNC:
		{
			std::cout << "ID_BULLET_SYNC" << std::endl;
		}
		break;

		case ID_PASSENGER_SYNC:
		{
			
		}
		break;

		case ID_UNOCCUPIED_SYNC:
		{
			
		}
		break;
	}

	return pSAMP->getRakClientInterface()->Send(bitStream, priority, reliability, orderingChannel);
}

Packet* HookedRakClientInterface::Receive(void)
{
	Packet *packet = pSAMP->getRakClientInterface()->Receive();

	if (packet != NULL && packet->data != NULL)
	{
		BYTE packetId = (BYTE)packet->data[0];

		switch (packetId)
		{
		case ID_CONNECTION_LOST:
		case ID_DISCONNECTION_NOTIFICATION:
		{
			break;
		}

		case ID_CONNECTION_BANNED:
		{

		}
		break;

		case ID_CONNECTION_REQUEST_ACCEPTED:
		{

		}
		break;
		}
	}

	return packet;
}

void HookedRakClientInterface::DeallocatePacket(Packet *packet)
{
	return pSAMP->getRakClientInterface()->DeallocatePacket(packet);
}

void HookedRakClientInterface::PingServer( void )
{
	pSAMP->getRakClientInterface()->PingServer();
}

void HookedRakClientInterface::PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections )
{
	pSAMP->getRakClientInterface()->PingServer( host, serverPort, clientPort, onlyReplyOnAcceptingConnections );
}

int HookedRakClientInterface::GetAveragePing( void )
{
	return pSAMP->getRakClientInterface()->GetAveragePing();
}

int HookedRakClientInterface::GetLastPing( void ) const
{
	return pSAMP->getRakClientInterface()->GetLastPing();
}

int HookedRakClientInterface::GetLowestPing( void ) const
{		
	return pSAMP->getRakClientInterface()->GetLowestPing();
}

int HookedRakClientInterface::GetPlayerPing( const PlayerID playerId )
{
	return pSAMP->getRakClientInterface()->GetPlayerPing( playerId );
}

void HookedRakClientInterface::StartOccasionalPing( void )
{
	pSAMP->getRakClientInterface()->StartOccasionalPing();
}

void HookedRakClientInterface::StopOccasionalPing( void )
{
	pSAMP->getRakClientInterface()->StopOccasionalPing();
}

bool HookedRakClientInterface::IsConnected( void ) const
{
	return pSAMP->getRakClientInterface()->IsConnected();
}

unsigned int HookedRakClientInterface::GetSynchronizedRandomInteger( void ) const
{
	return pSAMP->getRakClientInterface()->GetSynchronizedRandomInteger();
}

bool HookedRakClientInterface::GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer )
{
	return pSAMP->getRakClientInterface()->GenerateCompressionLayer( inputFrequencyTable, inputLayer );
}

bool HookedRakClientInterface::DeleteCompressionLayer( bool inputLayer )
{
	return pSAMP->getRakClientInterface()->DeleteCompressionLayer( inputLayer );
}

void HookedRakClientInterface::RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )
{
	pSAMP->getRakClientInterface()->RegisterAsRemoteProcedureCall( uniqueID, functionPointer );
}

void HookedRakClientInterface::RegisterClassMemberRPC( int* uniqueID, void *functionPointer )
{
	pSAMP->getRakClientInterface()->RegisterClassMemberRPC( uniqueID, functionPointer );
}

void HookedRakClientInterface::UnregisterAsRemoteProcedureCall( int* uniqueID )
{
	pSAMP->getRakClientInterface()->UnregisterAsRemoteProcedureCall( uniqueID );
}

bool HookedRakClientInterface::RPC( int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	return pSAMP->getRakClientInterface()->RPC( uniqueID, data, bitLength, priority, reliability, orderingChannel, shiftTimestamp );
}

bool HookedRakClientInterface::RPC(int* uniqueID, RakNet::BitStream *parameters, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp)
{
	return pSAMP->getRakClientInterface()->RPC(uniqueID, parameters, priority, reliability, orderingChannel, shiftTimestamp);
}

void HookedRakClientInterface::SetTrackFrequencyTable( bool b )
{
	pSAMP->getRakClientInterface()->SetTrackFrequencyTable( b );
}

bool HookedRakClientInterface::GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] )
{
	return pSAMP->getRakClientInterface()->GetSendFrequencyTable( outputFrequencyTable );
}

float HookedRakClientInterface::GetCompressionRatio( void ) const 
{
	return pSAMP->getRakClientInterface()->GetCompressionRatio();
}

float HookedRakClientInterface::GetDecompressionRatio( void ) const
{
	return pSAMP->getRakClientInterface()->GetDecompressionRatio();
}

void HookedRakClientInterface::AttachPlugin(PluginInterface *messageHandler)
{
	pSAMP->getRakClientInterface()->AttachPlugin(messageHandler);
}

void HookedRakClientInterface::DetachPlugin( PluginInterface *messageHandler )
{
	pSAMP->getRakClientInterface()->DetachPlugin(messageHandler);
}

RakNet::BitStream * HookedRakClientInterface::GetStaticServerData( void )
{
	return pSAMP->getRakClientInterface()->GetStaticServerData();
}

void HookedRakClientInterface::SetStaticServerData( const char *data, const int length )
{
	pSAMP->getRakClientInterface()->SetStaticServerData( data, length );
}

RakNet::BitStream * HookedRakClientInterface::GetStaticClientData( const PlayerID playerId )
{	
	return pSAMP->getRakClientInterface()->GetStaticClientData( playerId );
}

void HookedRakClientInterface::SetStaticClientData( const PlayerID playerId, const char *data, const int length )
{
	pSAMP->getRakClientInterface()->SetStaticClientData( playerId, data, length );
}

void HookedRakClientInterface::SendStaticClientDataToServer( void )
{
	pSAMP->getRakClientInterface()->SendStaticClientDataToServer();
}

PlayerID HookedRakClientInterface::GetServerID( void ) const
{
	return pSAMP->getRakClientInterface()->GetServerID();
}

PlayerID HookedRakClientInterface::GetPlayerID( void ) const
{
	return pSAMP->getRakClientInterface()->GetPlayerID();
}

PlayerID HookedRakClientInterface::GetInternalID( void ) const
{
	return pSAMP->getRakClientInterface()->GetInternalID();
}

const char* HookedRakClientInterface::PlayerIDToDottedIP( const PlayerID playerId ) const
{
	return pSAMP->getRakClientInterface()->PlayerIDToDottedIP( playerId );
}

void HookedRakClientInterface::PushBackPacket( Packet *packet, bool pushAtHead )
{
	pSAMP->getRakClientInterface()->PushBackPacket(packet, pushAtHead);
}

void HookedRakClientInterface::SetTimeoutTime( RakNetTime timeMS )
{
	pSAMP->getRakClientInterface()->SetTimeoutTime( timeMS );
}

bool HookedRakClientInterface::SetMTUSize( int size )
{
	return pSAMP->getRakClientInterface()->SetMTUSize( size );
}

int HookedRakClientInterface::GetMTUSize( void ) const
{
	return pSAMP->getRakClientInterface()->GetMTUSize();
}

void HookedRakClientInterface::AllowConnectionResponseIPMigration( bool allow )
{
	pSAMP->getRakClientInterface()->AllowConnectionResponseIPMigration( allow );
}

void HookedRakClientInterface::AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength )
{
	pSAMP->getRakClientInterface()->AdvertiseSystem( host, remotePort, data, dataLength );
}

RakNetStatisticsStruct* const HookedRakClientInterface::GetStatistics( void )
{
	return pSAMP->getRakClientInterface()->GetStatistics();
}

void HookedRakClientInterface::ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	pSAMP->getRakClientInterface()->ApplyNetworkSimulator( maxSendBPS, minExtraPing, extraPingVariance );
}

bool HookedRakClientInterface::IsNetworkSimulatorActive( void )
{
	return pSAMP->getRakClientInterface()->IsNetworkSimulatorActive();
}

PlayerIndex HookedRakClientInterface::GetPlayerIndex( void )
{
	return pSAMP->getRakClientInterface()->GetPlayerIndex();
}