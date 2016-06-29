// Copyright (c) 2016 The Uniqredit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UNIQREDIT_WALLET_RPCWALLET_H
#define UNIQREDIT_WALLET_RPCWALLET_H

class CRPCTable;

void RegisterWalletRPCCommands(CRPCTable &tableRPC);
extern void SendMoney(const CTxDestination &address, CAmount nValue, bool fSubtractFeeFromAmount, CWalletTx& wtxNew);
#endif //UNIQREDIT_WALLET_RPCWALLET_H
