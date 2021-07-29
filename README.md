# Optimistic-TCP-ACK-Attack-Simulation

An optimistic TCP ACK attack is a denial-of-service attack that makes
the congestion-control mechanism of TCP work against itself.
The Transmission Control Protocol (TCP) means to provide reliable
host-to-host transmission in a packet-switched computer network. In a
normal case, a TCP client acknowledges (ACKs) the receipt of packets
sent to it by the server. A TCP sender varies its transmission rate based
on receiving ACKs of the packets it sends. The number of TCP packets
allowed to be outstanding during a TCP communication session before
requiring an ACK is known as a congestion window. As a server
receives ACKs from a client, it dynamically adjusts the congestion
window size, w, to reflect the estimated bandwidth available. By this way,
the server sends packets and the client receives those and finally sends
ACKs to the server.

An optimistic ACK is an ACK sent by a client for a data segment that it
has not yet received by the client. A vulnerability exists in the potential
for a client to craft optimistic ACKs timed in such a way that they
correspond to legitimate packets that the sender has already injected
into the network (often referred to as "in-flight" packets). As a result, the
sender believes that the transfer is progressing better than it actually is
and may increase the rate at which it sends packets.
So in a nutshell, a rogue client tries to make a server increase its
sending rate until it runs out of bandwidth and cannot effectively serve
anyone else. If performed simultaneously against many servers, this
attack can also create Internet Wide congestion by overwhelming the
bandwidth resources of routers between the victims and attacker.
