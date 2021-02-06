/* Autogenerated SPL Token program C Bindings */

#pragma once

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * Minimum number of multisignature signers (min N)
 */
#define Token_MIN_SIGNERS 1

/**
 * Maximum number of multisignature signers (max N)
 */
#define Token_MAX_SIGNERS 11

/**
 * Account state.
 */
enum Token_AccountState
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
    /**
     * Account is not yet initialized
     */
    Token_AccountState_Uninitialized,
    /**
     * Account is initialized; the account owner and/or delegate may perform permitted operations
     * on this account
     */
    Token_AccountState_Initialized,
    /**
     * Account has been frozen by the mint freeze authority. Neither the account owner nor
     * the delegate are able to perform operations on this account.
     */
    Token_AccountState_Frozen,
};
#ifndef __cplusplus
typedef uint8_t Token_AccountState;
#endif // __cplusplus

/**
 * Specifies the authority type for SetAuthority instructions
 */
enum Token_AuthorityType
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
    /**
     * Authority to mint new tokens
     */
    Token_AuthorityType_MintTokens,
    /**
     * Authority to freeze any account associated with the Mint
     */
    Token_AuthorityType_FreezeAccount,
    /**
     * Owner of a given token account
     */
    Token_AuthorityType_AccountOwner,
    /**
     * Authority to close a token account
     */
    Token_AuthorityType_CloseAccount,
};
#ifndef __cplusplus
typedef uint8_t Token_AuthorityType;
#endif // __cplusplus

typedef uint8_t Token_Pubkey[32];

/**
 * A C representation of Rust's `std::option::Option`
 */
typedef enum Token_COption_Pubkey_Tag {
    /**
     * No value
     */
    Token_COption_Pubkey_None_Pubkey,
    /**
     * Some value `T`
     */
    Token_COption_Pubkey_Some_Pubkey,
} Token_COption_Pubkey_Tag;

typedef struct Token_COption_Pubkey {
    Token_COption_Pubkey_Tag tag;
    union {
        struct {
            Token_Pubkey some;
        };
    };
} Token_COption_Pubkey;

/**
 * Instructions supported by the token program.
 */
typedef enum Token_TokenInstruction_Tag {
    /**
     * Initializes a new mint and optionally deposits all the newly minted
     * tokens in an account.
     *
     * The `InitializeMint` instruction requires no signers and MUST be
     * included within the same Transaction as the system program's
     * `CreateInstruction` that creates the account being initialized.
     * Otherwise another party can acquire ownership of the uninitialized
     * account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]` The mint to initialize.
     *   1. `[]` Rent sysvar
     *
     */
    Token_TokenInstruction_InitializeMint,
    /**
     * Initializes a new account to hold tokens.  If this account is associated
     * with the native mint then the token balance of the initialized account
     * will be equal to the amount of SOL in the account. If this account is
     * associated with another mint, that mint must be initialized before this
     * command can succeed.
     *
     * The `InitializeAccount` instruction requires no signers and MUST be
     * included within the same Transaction as the system program's
     * `CreateInstruction` that creates the account being initialized.
     * Otherwise another party can acquire ownership of the uninitialized
     * account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]`  The account to initialize.
     *   1. `[]` The mint this account will be associated with.
     *   2. `[]` The new account's owner/multisignature.
     *   3. `[]` Rent sysvar
     */
    Token_TokenInstruction_InitializeAccount,
    /**
     * Initializes a multisignature account with N provided signers.
     *
     * Multisignature accounts can used in place of any single owner/delegate
     * accounts in any token instruction that require an owner/delegate to be
     * present.  The variant field represents the number of signers (M)
     * required to validate this multisignature account.
     *
     * The `InitializeMultisig` instruction requires no signers and MUST be
     * included within the same Transaction as the system program's
     * `CreateInstruction` that creates the account being initialized.
     * Otherwise another party can acquire ownership of the uninitialized
     * account.
     *
     * Accounts expected by this instruction:
     *
     *   0. `[writable]` The multisignature account to initialize.
     *   1. `[]` Rent sysvar
     *   2. ..2+N. `[]` The signer accounts, must equal to N where 1 <= N <=
     *      11.
     */
    Token_TokenInstruction_InitializeMultisig,
    /**
     * Transfers tokens from one account to another either directly or via a
     * delegate.  If this account is associated with the native mint then equal
     * amounts of SOL and Tokens will be transferred to the destination
     * account.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[writable]` The destination account.
     *   2. `[signer]` The source account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[writable]` The destination account.
     *   2. `[]` The source account's multisignature owner/delegate.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_Transfer,
    /**
     * Approves a delegate.  A delegate is given the authority over tokens on
     * behalf of the source account's owner.
     *
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
     *   2. `[]` The source account's multisignature owner.
     *   3. ..3+M `[signer]` M signer accounts
     */
    Token_TokenInstruction_Approve,
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
     *   1. `[]` The source account's multisignature owner.
     *   2. ..2+M `[signer]` M signer accounts
     */
    Token_TokenInstruction_Revoke,
    /**
     * Sets a new authority of a mint or account.
     *
     * Accounts expected by this instruction:
     *
     *   * Single authority
     *   0. `[writable]` The mint or account to change the authority of.
     *   1. `[signer]` The current authority of the mint or account.
     *
     *   * Multisignature authority
     *   0. `[writable]` The mint or account to change the authority of.
     *   1. `[]` The mint's or account's multisignature authority.
     *   2. ..2+M `[signer]` M signer accounts
     */
    Token_TokenInstruction_SetAuthority,
    /**
     * Mints new tokens to an account.  The native mint does not support
     * minting.
     *
     * Accounts expected by this instruction:
     *
     *   * Single authority
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[signer]` The mint's minting authority.
     *
     *   * Multisignature authority
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[]` The mint's multisignature mint-tokens authority.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_MintTo,
    /**
     * Burns tokens by removing them from an account.  `Burn` does not support
     * accounts associated with the native mint, use `CloseAccount` instead.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[writable]` The token mint.
     *   2. `[signer]` The account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[writable]` The token mint.
     *   2. `[]` The account's multisignature owner/delegate.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_Burn,
    /**
     * Close an account by transferring all its SOL to the destination account.
     * Non-native accounts may only be closed if its token amount is zero.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The account to close.
     *   1. `[writable]` The destination account.
     *   2. `[signer]` The account's owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The account to close.
     *   1. `[writable]` The destination account.
     *   2. `[]` The account's multisignature owner.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_CloseAccount,
    /**
     * Freeze an Initialized account using the Mint's freeze_authority (if
     * set).
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The account to freeze.
     *   1. `[]` The token mint.
     *   2. `[signer]` The mint freeze authority.
     *
     *   * Multisignature owner
     *   0. `[writable]` The account to freeze.
     *   1. `[]` The token mint.
     *   2. `[]` The mint's multisignature freeze authority.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_FreezeAccount,
    /**
     * Thaw a Frozen account using the Mint's freeze_authority (if set).
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The account to freeze.
     *   1. `[]` The token mint.
     *   2. `[signer]` The mint freeze authority.
     *
     *   * Multisignature owner
     *   0. `[writable]` The account to freeze.
     *   1. `[]` The token mint.
     *   2. `[]` The mint's multisignature freeze authority.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_ThawAccount,
    /**
     * Transfers tokens from one account to another either directly or via a
     * delegate.  If this account is associated with the native mint then equal
     * amounts of SOL and Tokens will be transferred to the destination
     * account.
     *
     * This instruction differs from Transfer in that the token mint and
     * decimals value is asserted by the caller.  This may be useful when
     * creating transactions offline or within a hardware wallet.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[]` The token mint.
     *   2. `[writable]` The destination account.
     *   3. `[signer]` The source account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The source account.
     *   1. `[]` The token mint.
     *   2. `[writable]` The destination account.
     *   3. `[]` The source account's multisignature owner/delegate.
     *   4. ..4+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_Transfer2,
    /**
     * Approves a delegate.  A delegate is given the authority over tokens on
     * behalf of the source account's owner.
     *
     * This instruction differs from Approve in that the token mint and
     * decimals value is asserted by the caller.  This may be useful when
     * creating transactions offline or within a hardware wallet.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner
     *   0. `[writable]` The source account.
     *   1. `[]` The token mint.
     *   2. `[]` The delegate.
     *   3. `[signer]` The source account owner.
     *
     *   * Multisignature owner
     *   0. `[writable]` The source account.
     *   1. `[]` The token mint.
     *   2. `[]` The delegate.
     *   3. `[]` The source account's multisignature owner.
     *   4. ..4+M `[signer]` M signer accounts
     */
    Token_TokenInstruction_Approve2,
    /**
     * Mints new tokens to an account.  The native mint does not support
     * minting.
     *
     * This instruction differs from MintTo in that the decimals value is
     * asserted by the caller.  This may be useful when creating transactions
     * offline or within a hardware wallet.
     *
     * Accounts expected by this instruction:
     *
     *   * Single authority
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[signer]` The mint's minting authority.
     *
     *   * Multisignature authority
     *   0. `[writable]` The mint.
     *   1. `[writable]` The account to mint tokens to.
     *   2. `[]` The mint's multisignature mint-tokens authority.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_MintTo2,
    /**
     * Burns tokens by removing them from an account.  `Burn2` does not
     * support accounts associated with the native mint, use `CloseAccount`
     * instead.
     *
     * This instruction differs from Burn in that the decimals value is asserted
     * by the caller. This may be useful when creating transactions offline or
     * within a hardware wallet.
     *
     * Accounts expected by this instruction:
     *
     *   * Single owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[writable]` The token mint.
     *   2. `[signer]` The account's owner/delegate.
     *
     *   * Multisignature owner/delegate
     *   0. `[writable]` The account to burn from.
     *   1. `[writable]` The token mint.
     *   2. `[]` The account's multisignature owner/delegate.
     *   3. ..3+M `[signer]` M signer accounts.
     */
    Token_TokenInstruction_Burn2,
} Token_TokenInstruction_Tag;

typedef struct Token_TokenInstruction_Token_InitializeMint_Body {
    /**
     * Number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
    /**
     * The authority/multisignature to mint tokens.
     */
    Token_Pubkey mint_authority;
    /**
     * The freeze authority/multisignature of the mint.
     */
    struct Token_COption_Pubkey freeze_authority;
} Token_TokenInstruction_Token_InitializeMint_Body;

typedef struct Token_TokenInstruction_Token_InitializeMultisig_Body {
    /**
     * The number of signers (M) required to validate this multisignature
     * account.
     */
    uint8_t m;
} Token_TokenInstruction_Token_InitializeMultisig_Body;

typedef struct Token_TokenInstruction_Token_Transfer_Body {
    /**
     * The amount of tokens to transfer.
     */
    uint64_t amount;
} Token_TokenInstruction_Token_Transfer_Body;

typedef struct Token_TokenInstruction_Token_Approve_Body {
    /**
     * The amount of tokens the delegate is approved for.
     */
    uint64_t amount;
} Token_TokenInstruction_Token_Approve_Body;

typedef struct Token_TokenInstruction_Token_SetAuthority_Body {
    /**
     * The type of authority to update.
     */
    Token_AuthorityType authority_type;
    /**
     * The new authority
     */
    struct Token_COption_Pubkey new_authority;
} Token_TokenInstruction_Token_SetAuthority_Body;

typedef struct Token_TokenInstruction_Token_MintTo_Body {
    /**
     * The amount of new tokens to mint.
     */
    uint64_t amount;
} Token_TokenInstruction_Token_MintTo_Body;

typedef struct Token_TokenInstruction_Token_Burn_Body {
    /**
     * The amount of tokens to burn.
     */
    uint64_t amount;
} Token_TokenInstruction_Token_Burn_Body;

typedef struct Token_TokenInstruction_Token_Transfer2_Body {
    /**
     * The amount of tokens to transfer.
     */
    uint64_t amount;
    /**
     * Expected number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
} Token_TokenInstruction_Token_Transfer2_Body;

typedef struct Token_TokenInstruction_Token_Approve2_Body {
    /**
     * The amount of tokens the delegate is approved for.
     */
    uint64_t amount;
    /**
     * Expected number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
} Token_TokenInstruction_Token_Approve2_Body;

typedef struct Token_TokenInstruction_Token_MintTo2_Body {
    /**
     * The amount of new tokens to mint.
     */
    uint64_t amount;
    /**
     * Expected number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
} Token_TokenInstruction_Token_MintTo2_Body;

typedef struct Token_TokenInstruction_Token_Burn2_Body {
    /**
     * The amount of tokens to burn.
     */
    uint64_t amount;
    /**
     * Expected number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
} Token_TokenInstruction_Token_Burn2_Body;

typedef struct Token_TokenInstruction {
    Token_TokenInstruction_Tag tag;
    union {
        Token_TokenInstruction_Token_InitializeMint_Body initialize_mint;
        Token_TokenInstruction_Token_InitializeMultisig_Body initialize_multisig;
        Token_TokenInstruction_Token_Transfer_Body transfer;
        Token_TokenInstruction_Token_Approve_Body approve;
        Token_TokenInstruction_Token_SetAuthority_Body set_authority;
        Token_TokenInstruction_Token_MintTo_Body mint_to;
        Token_TokenInstruction_Token_Burn_Body burn;
        Token_TokenInstruction_Token_Transfer2_Body transfer2;
        Token_TokenInstruction_Token_Approve2_Body approve2;
        Token_TokenInstruction_Token_MintTo2_Body mint_to2;
        Token_TokenInstruction_Token_Burn2_Body burn2;
    };
} Token_TokenInstruction;

/**
 * Mint data.
 */
typedef struct Token_Mint {
    /**
     * Optional authority used to mint new tokens. The mint authority may only be provided during
     * mint creation. If no mint authority is present then the mint has a fixed supply and no
     * further tokens may be minted.
     */
    struct Token_COption_Pubkey mint_authority;
    /**
     * Total supply of tokens.
     */
    uint64_t supply;
    /**
     * Number of base 10 digits to the right of the decimal place.
     */
    uint8_t decimals;
    /**
     * Is `true` if this structure has been initialized
     */
    bool is_initialized;
    /**
     * Optional authority to freeze token accounts.
     */
    struct Token_COption_Pubkey freeze_authority;
} Token_Mint;

/**
 * A C representation of Rust's `std::option::Option`
 */
typedef enum Token_COption_u64_Tag {
    /**
     * No value
     */
    Token_COption_u64_None_u64,
    /**
     * Some value `T`
     */
    Token_COption_u64_Some_u64,
} Token_COption_u64_Tag;

typedef struct Token_COption_u64 {
    Token_COption_u64_Tag tag;
    union {
        struct {
            uint64_t some;
        };
    };
} Token_COption_u64;

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
    struct Token_COption_Pubkey delegate;
    /**
     * The account's state
     */
    Token_AccountState state;
    /**
     * If is_some, this is a native token, and the value logs the rent-exempt reserve. An Account
     * is required to be rent-exempt, so the value is used by the Processor to ensure that wrapped
     * SOL accounts do not drop below this threshold.
     */
    struct Token_COption_u64 is_native;
    /**
     * The amount delegated
     */
    uint64_t delegated_amount;
    /**
     * Optional authority to close the account.
     */
    struct Token_COption_Pubkey close_authority;
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
