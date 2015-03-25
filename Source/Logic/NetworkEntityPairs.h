/**
 * this file contains {NetworkEntity} pairs which defines which subclass of a
 *   {NetworkEntity} instance server side is logically linked to which subclass
 *   of a {NetworkEntity} instance client side.
 *
 * A {NetworkEntity} on the server is logically linked to a {NetworkEntity} on
 *   the client, but these {NetworkEntity} instances usually are not instances
 *   of the same class, because they need to behave differently since one is on
 *   the server side, and the other is client side.
 *
 *
 */

/**
 * a {Player} instance on the server side is connected to a {Command} instance
 *   on the client side.
 */
#define NET_ENT_PAIR_PLAYER_COMMAND 0

/**
 * a {PlayerController} instance on the server side is connected to a {Command}
 *   instance on the client side.
 */
#define NET_ENT_PAIR_PLAYERCONTROLLER_NETCONTROLLER 1
