/* Autogenerated SPL Token program C Bindings */

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define TOKEN_MAJOR_VERSION 1
#define TOKEN_MINOR_VERSION 0
#define TOKEN_PATCH_VERSION 0

/**
 * Maximum number of multisignature signers (max N)
 */
#define Token_MAX_SIGNERS 11

/**
 * Minimum number of multisignature signers (min N)
 */
#define Token_MIN_SIGNERS 1

/**
 * Instructions supported by the token program.
 */
typedef enum Token_TokenInstruction_Tag {
    /**
     * Initializes a new mint and optionally deposits all the newly minted tokens in an account.
     *
     * The `InitializeMint` instruction requires no signers and MUST be included within
     * the same Transaction as the system program's `CreateInstruction` that creates the account
     * being initialized.  Otherwise another party can acquire ownership of the uninitialized account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]` The mint to initialize.
     *   1.
     *      * If supply is non-zero: `[writable]` The account to hold all the newly minted tokens.
     *      * If supply is zero: `[]` The owner/multisignature of the mint.
     *   2. `[]` (optional) The owner/multisignature of the mint if supply is non-zero, if
     *                      present then further minting is supported.
     *
     */
    InitializeMint,
    /**
     * Initializes a new account to hold tokens.  If this account is associated with the native mint
     * then the token balance of the initialized account will be equal to the amount of SOL in the account.
     *
     * The `InitializeAccount` instruction requires no signers and MUST be included within
     * the same Transaction as the system program's `CreateInstruction` that creates the account
     * being initialized.  Otherwise another party can acquire ownership of the uninitialized account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]`  The account to initialize.
     *   1. `[]` The mint this account will be associated with.
     *   2. `[]` The new account's owner/multisignature.
     */
    InitializeAccount,
    /**
     * Initializes a multisignature account with N provided signers.
     *
     * Multisignature accounts can used in place of any single owner/delegate accounts in any
     * token instruction that require an owner/delegate to be present.  The variant field represents the
     * number of signers (M) required to validate this multisignature account.
     *
     * The `InitializeMultisig` instruction requires no signers and MUST be included within
     * the same Transaction as the system program's `CreateInstruction` that creates the account
     * being initialized.  Otherwise another party can acquire ownership of the uninitialized account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]` The multisignature account to initialize.
     *   1. ..1+N. `[]` The signer accounts, must equal to N where 1 <= N <= 11.
     */
    InitializeMultisig,
    /**
     * Transfers tokens from one account to another either directly or via a delegate.  If this
     * account is associated with the native mint then equal amounts of SOL and Tokens will be
     * transferred to the destination account.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[writable]` The destination account.
     *   2. '[signer]' The source account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[writable]` The destination account.
     *   2. '[]' The source account's multisignature owner/delegate.
     *   3. ..3+M '[signer]' M signer accounts.
     */
    Transfer,
    /**
     * Approves a delegate.  A delegate is given the authority over
     * tokens on behalf of the source account's owner.
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The source account.
     *   1. `[]` The delegate.
     *   2. `[signer]` The source account owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The source account.
     *   1. `[]` The delegate.
     *   2. '[]' The source account's multisignature owner.
     *   3. ..3+M '[signer]' M signer accounts
     */
    Approve,
    /**
     * Revokes the delegate's authority.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The source account.
     *   1. `[signer]` The source account owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The source account.
     *   1. '[]' The source account's multisignature owner.
     *   2. ..2+M '[signer]' M signer accounts
     */
    Revoke,
    /**
     * Sets a new owner of a mint or account.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The mint or account to change the owner of.
     *   1. `[]` The new owner/delegate/multisignature.
     *   2. `[signer]` The owner of the mint or account.
     *
     *   * Multisignature owner
     *   0. `[writable]` The mint or account to change the owner of.
     *   1. `[]` The new owner/delegate/multisignature.
     *   2. `[]` The mint's or account's multisignature owner.
     *   3. ..3+M '[signer]' M signer accounts
     */
    SetOwner,
    /**
     * Mints new tokens to an account.  The native mint does not support minting.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[signer]` The mint's owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[]` The mint's multisignature owner.
     *   3. ..3+M '[signer]' M signer accounts.
     */
    MintTo,
    /**
     * Burns tokens by removing them from an account.  `Burn` does not support accounts
     * associated with the native mint, use `CloseAccount` instead.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[signer]` The account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[]` The account's multisignature owner/delegate.
     *   2. ..2+M '[signer]' M signer accounts.
     */
    Burn,
    /**
     * Close an account by transferring all its SOL to the destination account.
     * Non-native accounts may only be closed if its token amount is zero.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The account to close.
     *   1. '[writable]' The destination account.
     *   2. `[signer]` The account's owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The account to close.
     *   1. '[writable]' The destination account.
     *   2. `[]` The account's multisignature owner.
     *   3. ..3+M '[signer]' M signer accounts.
     */
    CloseAccount,
} Token_TokenInstruction_Tag;

typedef struct Token_InitializeMint_Body {
    /**
     * Initial amount of tokens to mint.
     */
    uint64_t amount;
    /**
     * Number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
} Token_InitializeMint_Body;

typedef struct Token_InitializeMultisig_Body {
    /**
     * The number of signers (M) required to validate this multisignature account.
     */
    uint8_t m;
} Token_InitializeMultisig_Body;

typedef struct Token_Transfer_Body {
    /**
     * The amount of tokens to transfer.
     */
    uint64_t amount;
} Token_Transfer_Body;

typedef struct Token_Approve_Body {
    /**
     * The amount of tokens the delegate is approved for.
     */
    uint64_t amount;
} Token_Approve_Body;

typedef struct Token_MintTo_Body {
    /**
     * The amount of new tokens to mint.
     */
    uint64_t amount;
} Token_MintTo_Body;

typedef struct Token_Burn_Body {
    /**
     * The amount of tokens to burn.
     */
    uint64_t amount;
} Token_Burn_Body;

typedef struct Token_TokenInstruction {
    Token_TokenInstruction_Tag tag;
    union {
        Token_InitializeMint_Body initialize_mint;
        Token_InitializeMultisig_Body initialize_multisig;
        Token_Transfer_Body transfer;
        Token_Approve_Body approve;
        Token_MintTo_Body mint_to;
        Token_Burn_Body burn;
    };
} Token_TokenInstruction;

typedef uint8_t Token_Pubkey[32];

/**
 * A C representation of Rust's `std::option::Option`
 */
typedef enum Token_COption_Pubkey_Tag {
    /**
     * No value
     */
    None_Pubkey,
    /**
     * Some value `T`
     */
    Some_Pubkey,
} Token_COption_Pubkey_Tag;

typedef struct Token_Some_Body_Pubkey {
    Token_Pubkey _0;
} Token_Some_Body_Pubkey;

typedef struct Token_COption_Pubkey {
    Token_COption_Pubkey_Tag tag;
    union {
        Token_Some_Body_Pubkey some;
    };
} Token_COption_Pubkey;

/**
 * Mint data.
 */
typedef struct Token_Mint {
    /**
     * Optional owner, used to mint new tokens.  The owner may only
     * be provided during mint creation.  If no owner is present then the mint
     * has a fixed supply and no further tokens may be minted.
     */
    Token_COption_Pubkey owner;
    /**
     * Number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
    /**
     * Is `true` if this structure has been initialized
     */
    bool is_initialized;
} Token_Mint;

/**
 * Account data.
 */
typedef struct Token_Account {
    /**
     * The mint associated with this account
     */
    Token_Pubkey mint;
    /**
     * The owner of this account.
     */
    Token_Pubkey owner;
    /**
     * The amount of tokens this account holds.
     */
    uint64_t amount;
    /**
     * If `delegate` is `Some` then `delegated_amount` represents
     * the amount authorized by the delegate
     */
    Token_COption_Pubkey delegate;
    /**
     * Is `true` if this structure has been initialized
     */
    bool is_initialized;
    /**
     * Is this a native token
     */
    bool is_native;
    /**
     * The amount delegated
     */
    uint64_t delegated_amount;
} Token_Account;

/**
 * Multisignature data.
 */
typedef struct Token_Multisig {
    /**
     * Number of signers required
     */
    uint8_t m;
    /**
     * Number of valid signers
     */
    uint8_t n;
    /**
     * Is `true` if this structure has been initialized
     */
    bool is_initialized;
    /**
     * Signer public keys
     */
    Token_Pubkey signers[Token_MAX_SIGNERS];
} Token_Multisig;
