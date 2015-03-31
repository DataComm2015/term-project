#ifndef NETWORK_ENTITY_PAIRS
#define NETWORK_ENTITY_PAIRS

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

enum class NetworkEntityPair
{
    /**
     * a {Player} instance on the server side is connected to a {Command} instance
     *   on the client side.
     */
    PLAYER_COMMAND,
    /**
     * a {PlayerController} instance on the server side is connected to a {Command}
     *   instance on the client side.
     */
    SERVERCONTROLLER_NETCONTROLLER,
    /**
     * a {ServerGameState} instance on the server side is connected to a
     *   {ClientGameState} instance on the client side.
     */
    SERVERGAMESTATE_CLIENTGAMESTATE
};

//////////////////////////////////////////////////////////////////////////////
// message types used to between a {Player} {NetworkEntity} and a {Command} //
// {NetworkEntity}.                                                         //
//////////////////////////////////////////////////////////////////////////////

enum class PlayerCommandMsgType
{
    /**
     * {Command} instance is sending a "start moving left" command to the {Player}
     *   instance.
     */
    START_MV_LEFT_COMMAND,
    /**
     * {Command} instance is sending a "start moving right" command to the {Player}
     *   instance.
     */
    START_MV_RIGHT_COMMAND,
    /**
     * {Command} instance is sending a "start moving up" command to the {Player}
     *   instance.
     */
    START_MV_UP_COMMAND,
    /**
     * {Command} instance is sending a "start moving down" command to the {Player}
     *   instance.
     */
    START_MV_DOWN_COMMAND,
    /**
     * {Command} instance is sending a "stop moving left" command to the {Player}
     *   instance.
     */
    STOP_MV_LEFT_COMMAND,
    /**
     * {Command} instance is sending a "stop moving right" command to the {Player}
     *   instance.
     */
    STOP_MV_RIGHT_COMMAND,
    /**
     * {Command} instance is sending a "stop moving up" command to the {Player}
     *   instance.
     */
    STOP_MV_UP_COMMAND,
    /**
     * {Command} instance is sending a "stop moving down" command to the {Player}
     *   instance.
     */
    STOP_MV_DOWN_COMMAND,
    /**
     * Server message sent to clients to change their player mode (VESSEL, DEITY, GHOST)
     */
    SET_MODE,
    /**
     * Client -> Server Message informing server of client lobby option selections
     */
    SELECT_LOBBY_OPTIONS
};

////////////////////////////////////////////////////////////////////////////////
// message types used to between a {ServerGameState} and a {ClientGameState}. //
////////////////////////////////////////////////////////////////////////////////

enum class ServerGameStateClientGameStateMsgType
{
    /**
     * {ServerGameState} instance is sending a "start game scene" command to the
     *   {ClientGameState} instance.
     */
    START_GAME_SCENE,
    /**
     * {ServerGameState} instance is sending a "start lobby scene" command to the
     *   {ClientGameState} instance.
     */
    START_LOBBY_SCENE,
    /**
     * Server message sent to clients to indicate that a new player has connected.
     */
    PLAYER_CONNECTED,
    /**
     * Server message sent to clients to indicate that a player has disconnected.
     */
    PLAYER_DISCONNECTED,
    /**
     * Server message sent to clients to indicate that lobby countdown is
     * continuing.
     */
    LOBBY_COUNTDOWN_START,
    /**
     * Server message sent to clients to indicate that lobby countdown is
     * paused.
     */
    LOBBY_COUNTDOWN_STOP,
    /**
     * Server -> Client Request options before starting game
     */
    READY_FOR_GAME
};

#endif
