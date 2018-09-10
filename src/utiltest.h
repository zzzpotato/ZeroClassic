// Copyright (c) 2016 The Zero developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "wallet/wallet.h"
#include "zero/JoinSplit.hpp"
#include "zero/Note.hpp"
#include "zero/NoteEncryption.hpp"

CWalletTx GetValidReceive(ZCJoinSplit& params,
                          const libzero::SpendingKey& sk, CAmount value,
                          bool randomInputs);
libzero::Note GetNote(ZCJoinSplit& params,
                       const libzero::SpendingKey& sk,
                       const CTransaction& tx, size_t js, size_t n);
CWalletTx GetValidSpend(ZCJoinSplit& params,
                        const libzero::SpendingKey& sk,
                        const libzero::Note& note, CAmount value);
