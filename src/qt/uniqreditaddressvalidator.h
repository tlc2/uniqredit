// Copyright (c) 2011-2014 The Uniqredit Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef UNIQREDIT_QT_UNIQREDITADDRESSVALIDATOR_H
#define UNIQREDIT_QT_UNIQREDITADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class UniqreditAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UniqreditAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Uniqredit address widget validator, checks for a valid uniqredit address.
 */
class UniqreditAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit UniqreditAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // UNIQREDIT_QT_UNIQREDITADDRESSVALIDATOR_H
