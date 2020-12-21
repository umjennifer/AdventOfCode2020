import re


def get_fake_lines():
    return [
        "2-8 t: pncmjxlvckfbtrjh",
        "8-9 l: lzllllldsl",
        "3-11 c: ccchcccccclxnkcmc",
    ]


def get_lines():
    with open("foo.txt") as f:
        return [line.rstrip()for line in f.readlines()]


def get_policy_and_passwords_from_lines(lines):
    prog = re.compile("(\d{1,3})-(\d{1,3}) (\D): (\S*)")
    return [prog.search(line).groups() for line in lines]


def number_of_valid_passwords_p2(policies):
    count = 0
    for lower, upper, character, pw in policies:
        if (pw[int(lower) - 1] == character) ^ (pw[int(upper) - 1] == character):
            count += 1
    return count


def number_of_valid_passwords_p1(policies):
    count = 0
    for lower, upper, character, pw in policies:
        char_count = pw.count(character)
        if char_count >= int(lower) and char_count <= int(upper):
            count += 1
    return count


def main():
    lines = get_lines()
    policies = get_policy_and_passwords_from_lines(lines)
    print(number_of_valid_passwords_p1(policies))
    print(number_of_valid_passwords_p2(policies))


main()
