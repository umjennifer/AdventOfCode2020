def get_lines_from_file(filename):
    with open(filename) as f:
        return [line.rstrip() for line in f] + [""]


def parse_lines_d2(lines):
    count = 0
    group_set = set()
    new_person = True
    for line in lines:
        if line == "":
            print(len(group_set))
            count += len(group_set)
            group_set.clear()
            print("----")
            new_person = True
            continue
        else:
            if new_person:
                group_set = set(line)
            else:
                group_set &= set(line)  # This is the reason I went Python :)
            print(group_set)
            new_person = False
    print(count)


def main():
    lines = get_lines_from_file("foo.txt")
    parse_lines_d2(lines)


if __name__ == "__main__":
    main()
