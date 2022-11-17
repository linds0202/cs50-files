def main():
    while True:
        num = input("Credit Card Number: ")
        if num.isdecimal():
            break
    validate(num)

def validate(card):
    length = len(card)
    if sum_digits(card) == False:
        print("INVALID")
    elif length == 15:
        if int(card[:2]) == 34 or int(card[:2]):
            print("AMEX")
    elif int(card[0]) == 4:
        if length ==13 or length == 16:
            print("VISA")
    elif length == 16:
        if int(card[:2]) > 50 and int(card[:2]) < 56:
            print("MASTERCARD")
    else:
        print("INVALID")


def sum_digits(card_num):
    sum = 0
    for i in range((len(card_num) - 2), -1, -2):
        digit = int(card_num[i])*2
        if digit > 9:
            sum += (digit - 10) + 1
        else:
            sum += digit
    for i in range(len(card_num) - 1, -1, -2):
        digit = int(card_num[i])
        sum += digit
    if sum % 2 == 0:
        return True
    else:
        return False

main()