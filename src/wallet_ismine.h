// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_ISMINE_H
#define BITCOIN_WALLET_ISMINE_H

#include "key.h"
#include "script/standard.h"

class CKeyStore;
class CScript;

/** IsMine() return codes */
enum isminetype {
    ISMINE_NO = 0,
    //! Indicates that we dont know how to create a scriptSig that would solve this if we were given the appropriate private keys
    ISMINE_WATCH_ONLY = 1,
    //! Indicates that we know how to create a scriptSig that would solve this if we were given the appropriate private keys
    ISMINE_MULTISIG = 2,
    ISMINE_SPENDABLE  = 4,
    ISMINE_ALL = ISMINE_WATCH_ONLY | ISMINE_SPENDABLE
};
/** used for bitflags of isminetype */
typedef uint8_t isminefilter;

/* isInvalid becomes true when the script is found invalid by consensus or policy. This will terminate the recursion
 * and return a ISMINE_NO immediately, as an invalid script should never be considered as "mine". This is needed as
 * different SIGVERSION may have different network rules. Currently the only use of isInvalid is indicate uncompressed
 * keys in SIGVERSION_WITNESS_V0 script, but could also be used in similar cases in the future
 */
isminetype IsMine(const CKeyStore& keystore, const CScript& scriptPubKey, bool& isInvalid, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CScript& scriptPubKey, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CTxDestination& dest, bool& isInvalid, SigVersion = SIGVERSION_BASE);
isminetype IsMine(const CKeyStore& keystore, const CTxDestination& dest, SigVersion = SIGVERSION_BASE);

#endif // BITCOIN_WALLET_ISMINE_H
