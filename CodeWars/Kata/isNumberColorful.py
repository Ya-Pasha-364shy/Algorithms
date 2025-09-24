
counter = 1

def checker(calculated_value, expected_value):
    global counter
    if calculated_value == expected_value:
        counter += 1
    else:
        print(f"Test {counter} failed: expected {expected_value}, but occured {calculated_value}")
        exit(1)

# Description:
# 
# Determine whether a non-negative integer number is colorful or not.
# 263 is a colorful number because [2, 6, 3, 2*6, 6*3, 2*6*3] are all different; whereas
# 236 is not colorful, because [2, 3, 6, 2*3, 3*6, 2*3*6] has 6 twice.

def colorful(number):
    b = 1
    a = 10
    bitmap1 = int()
    bitmap2 = int()
    bitmap3 = int()
    bitmap4 = int()
    arr = list()

    next_number = (number % a) // b 
    while 1:
        if bitmap1 & (1 << next_number):
            return False 
        bitmap1 |= 1 << next_number
        arr.append(next_number)

        a *= 10
        b *= 10
        next_number = (number % a) // b
        if next_number == 0:
            break

    for i in range(1, len(arr)):
        next_number = arr[i] * arr[i-1]
        if next_number < 32:
            test_bit = 1 << next_number
            if bitmap1 & test_bit:
                return False
            bitmap1 |= test_bit
        elif next_number >= 32 and next_number < 64:
            test_bit = 1 << (next_number % 32)
            if bitmap2 & test_bit:
                return False
            bitmap2 |= test_bit
        elif next_number >= 64 and next_number < 96:
            test_bit = 1 << (next_number % 64)
            if bitmap3 & test_bit:
                return False
            bitmap3 |= 1 << test_bit
        else:
            test_bit = 1 << (next_number % 96)
            if bitmap4 & test_bit:
                return False
            bitmap4 |= 1 << test_bit

    return True

def main():
    checker(colorful(55), False)
    checker(colorful(5), True)
    checker(colorful(23), True)
    checker(colorful(263), True)
    checker(colorful(235789), True)
    checker(colorful(50), False)
    checker(colorful(13), False)
    checker(colorful(236), False)
    checker(colorful(2357893), False)
    print("All tests OK")

main()