import random
import string

def generate_code():
    return ''.join(random.choices(string.ascii_uppercase + string.digits, k=4))

with open("test_data.txt", "w") as f:
    for i in range(30):
        package_id = f"SF{random.randint(100000, 999999)}"
        phone = f"138{random.randint(10000000, 99999999):08d}"
        status = random.choice([0, 1, 2])
        code = generate_code()
        f.write(f"{package_id},{phone},{status},{code}\n")
