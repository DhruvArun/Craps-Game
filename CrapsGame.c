#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DIE_SIDES 6
#define MIN_BET 5
#define TRUE 1
#define FALSE 0

int getWallet(void);
int makeBet(int);
int doAgain(void);
void goodbye(int);
int playRound(void);
int rollForPoint(int);
int rollDice(void);
int rollDie(void);

int main(void)
{
    int wallet;
    int bet;

    /* This call is important to ensure the pseudo-random number
     * generator doesn't always give us the same random values. */
    srand((unsigned)time(NULL));

    wallet = getWallet();

    do
    {
        bet = makeBet(wallet);
        if (playRound())
        {
            printf("You win!\n");
            wallet += bet;
        }
        else
        {
            printf("You lose!\n");
            wallet -= bet;
        }
    } while (wallet >= MIN_BET && doAgain());

    goodbye(wallet);

    return 0;
}

/*
 * Prompts the user for the amount of money they have to play with - assumed to be
 * measured in whole dollars.  Rejects values that are not at least MIN_BET in size
 * and prompts for another value until a value of size MIN_BET dollars or greater
 * is entered.
 * Returns: amount of money entered by user (a positive, integer dollar value)
 */
int getWallet(void)
{
    int wallet;

    printf("How much money do you have to play with?\n");
    scanf("%d", &wallet);

    while (wallet < MIN_BET)
    {
        printf("You must have at least $%d to play the game...\n", MIN_BET);

        printf("How much money do you have to play with?\n");
        scanf("%d", &wallet);
    }
    return wallet;
}

/*
 * Prompts user to make a bet (minimum value $MIN_BET, maximum value $wallet)
 * Keeps prompting user until a value of at least $MIN_BET but no more than $wallet
 * is entered.
 * Parameter: wallet - the amount in the user's wallet
 * Returns: user's bet (minimum $MIN_BET)
 */
int makeBet(int wallet)
{
    int bet;

    printf("\n\nYou have $%d in your wallet.\n", wallet);
    printf("Place your bet (minimum $%d): ", MIN_BET);
    scanf("%d", &bet);

    while (bet < MIN_BET || bet > wallet)
    {
        if (bet < MIN_BET)
            printf("Your bet is below the minimum of $%d, try again.\n", MIN_BET);
        else
            printf("You've bet more than you have in your wallet, try again.\n");

        printf("\n\nYou have $%d in your wallet.\n", wallet);
        printf("Place your bet (minimum $%d): ", MIN_BET);
        scanf("%d", &bet);
    }

    return bet;
}

/*
 * Ask user if they want to play again.
 * Returns: true if user wants to play again, false otherwise.
 */
int doAgain(void)
{
    int response;

    printf("Enter 1 to play again, 0 to quit:\n");
    scanf("%d", &response);

    return response;
}

/*
 * Prints goodbye message to user based on whether or not they
 * went broke while playing the game.  Tells the user they're broke
 * if they have less than MIN_BET in their wallet, otherwise tells
 * them how much they have in their wallet.
 * Parameter: wallet - amount of money in wallet
 */
void goodbye(int wallet)
{
    if (wallet < MIN_BET)
        printf("\nSorry, you're broke...\n");
    else
        printf("\nYou have $%d left in your wallet. Goodbye!\n", wallet);
}

/*
 * Plays a single round of craps with the user.
 * Returns: true if user won round, false otherwise.
 */
int playRound(void)
{
    int myRoll;
    int point;
    int wonRound;

    myRoll = rollDice();
    printf("You rolled a %d.\n", myRoll);

    if (myRoll == 2 || myRoll == 3 || myRoll == 12)
    {
        wonRound = FALSE;
    }
    else if (myRoll == 7 || myRoll == 11)
    {
        wonRound = TRUE;
    }
    else
    {
        point = myRoll;
        printf("\nRolling for point: %d...\n", point);
        wonRound = rollForPoint(point);
    }

    return wonRound;
}

/*
 * Repeatedly rolls dice until either the point value or the value 7 is rolled.
 * Parameter: point - the current point value
 * Returns: true if user rolled point value before rolling a 7 (user won round),
 * false otherwise (user lost round)
 */
int rollForPoint(int point)
{
    int gotPoint = FALSE;
    int myRoll;

    myRoll = rollDice();
    printf("You rolled a %d.\n", myRoll);

    while (myRoll != point && myRoll != 7)
    {
        myRoll = rollDice();
        printf("You rolled a %d.\n", myRoll);
    }

    if (myRoll == point)
        gotPoint = TRUE;

    return gotPoint;
}

/*
 * Rolls a pair of dice.
 * Returns: sum of face values rolled
 */
int rollDice(void)
{
    return rollDie() + rollDie();
}

/*
 * Rolls a single die.
 * Returns: face value rolled
 */
int rollDie(void)
{
    return (rand() % DIE_SIDES + 1);
}