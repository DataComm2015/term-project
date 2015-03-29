/**
 * this file contains {NetworkEntity} pairs which defines which subclass of a
 *   {NetworkEntity} instance server side is logically linked to which subclass
 *   of a {NetworkEntity} instance client side.
 *
 * this file also contains message types exchanged between each of the defined
 *   pairs. this is used for multiplexing of messages for each of the
 *   connections.
 *
 * A {NetworkEntity} on the server is logically linked to a {NetworkEntity} on
 *   the client, but these {NetworkEntity} instances usually are not instances
 *   of the same class, because they need to behave differently since one is on
 *   the server side, and the other is client side.
 */

///////////////////////////////
// network entity pair types //
///////////////////////////////

/**
 * a {Player} instance on the server side is connected to a {Command} instance
 *   on the client side.
 */
#define NET_ENT_PAIR_PLAYER_COMMAND 0

/**
 * a {PlayerController} instance on the server side is connected to a {Command}
 *   instance on the client side.
 */
#define NET_ENT_PAIR_SERVERCONTROLLER_NETCONTROLLER 1

//////////////////////////////////////////////////////////////////////////////
// message types used to between a {Player} {NetworkEntity} and a {Command} //
// {NetworkEntity}.                                                         //
//////////////////////////////////////////////////////////////////////////////

/**
 * {Command} instance is sending a "start moving left" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_START_MV_LEFT_COMMAND 0

/**
 * {Command} instance is sending a "start moving right" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_START_MV_RIGHT_COMMAND 1

/**
 * {Command} instance is sending a "start moving up" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_START_MV_UP_COMMAND 2

/**
 * {Command} instance is sending a "start moving down" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_START_MV_DOWN_COMMAND 3

/**
 * {Command} instance is sending a "stop moving left" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_STOP_MV_LEFT_COMMAND 4

/**
 * {Command} instance is sending a "stop moving right" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_STOP_MV_RIGHT_COMMAND 5

/**
 * {Command} instance is sending a "stop moving up" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_STOP_MV_UP_COMMAND 6

/**
 * {Command} instance is sending a "stop moving down" command to the {Player}
 *   instance.
 */
#define MSG_T_PLAYER_COMMAND_STOP_MV_DOWN_COMMAND 7

/**
 * Server message sent to clients to indicate that a new player has connected.
 */
#define MSG_T_PLAYER_CONNECTED 10

/**
 * Server message sent to clients to indicate that a player has disconnected.
 */
#define MSG_T_PLAYER_DISCONNECTED 11

/**
 * Server message sent to clients to indicate that lobby countdown is
 * continuing.
 */
#define MSG_T_LOBBY_COUNTDOWN_START 12

/**
 * Server message sent to clients to indicate that lobby countdown is
 * paused.
 */
#define MSG_T_LOBBY_COUNTDOWN_STOP 13

//////////////////////////////////////////////////////////////////////////////
// message types used to between a {ServerController} {NetworkEntity} and a //
// {NetworkController} {NetworkEntity}.                                     //
//////////////////////////////////////////////////////////////////////////////

/**
 * server is sending a "make a vessel" command to the client using onRegister,
 *   registering the {ServerCommandEntity} with the client.
 */
#define MSG_T_SERVERCONTROLLER_NETCONTROLLER_MAKE_VESSEL 0
