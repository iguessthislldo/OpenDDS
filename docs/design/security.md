# OpenDDS Security

This document is intended as a collection of high-level notes on OpenDDS
Security. OpenDDS Security provides security controls and capabilities for RTPS
including authentication of participants and encryption of messages. It an
implementation of DDS Security Version 1.1 (OMG formal/2018-04-01). Please
refer to the latest version of DDS Security for ultimately how security should
work.

## Authentication

Authentication occurs when participants discover each other. Based on the
GUIDs, one side will become the authentication leader, and it send an
authentication request, which contains it's signed governance and permissions
documents, to the other participant, which we will call the authentication
follower. This is all done using the builtin SDP participant readers and
writers. The follower will verify the leader's documents in the request and
return their documents in reply. The leader will then verify the followers
reply and send a final message to the follower which completes authentication.

## Key Exchange

During key exchange all keys of secure entities will be exchanged using the
"Builtin Participant Volatile Message Secure" topic. This can be described as a
boot strap to the ultimate security. The order of this isn't dependent on
order like authentication is. Each side should send at least 8 keys, one for
each entity.

## Fake Encryption

Anyone debugging OpenDDS security to any significant extent will probably find
the fake encryption option useful. It disables all encryption in OpenDDS
Security, but leaves the rest of the infrastructure alone. This allows one to
see what is being sent in Wireshark.

To enable it, pass `-DCPSSecurityFakeEncryption=1` to all programs using
security. If all participants are not set the same, it will cause secuirty to
fail. It can also be set in the common section of ini files. Refer to the RTPS
and Security Specs for the structure of Secure RTPS packets to aid in mannually
demarshaling them.
