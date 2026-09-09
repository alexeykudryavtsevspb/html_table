import random

N = 3000
MAX_COORD = 1000
MAX_SIDE = 50

def intersects(r1, r2):
    x1_1, y1_1, x2_1, y2_1 = r1
    x1_2, y1_2, x2_2, y2_2 = r2
    return not (x2_1 <= x1_2 or x1_1 >= x2_2 or y2_1 <= y1_2 or y1_1 >= y2_2)

rects = []
attempts = 0

while len(rects) < N and attempts < 100000:
    attempts += 1
    w = random.randint(1, MAX_SIDE)
    h = random.randint(1, MAX_SIDE)
    x1 = random.randint(0, MAX_COORD - w)
    y1 = random.randint(0, MAX_COORD - h)
    candidate = (x1, y1, x1 + w, y1 + h)

    if not any(intersects(candidate, r) for r in rects):
        rects.append(candidate)

with open("sample.txt", "w") as f:
    for r in rects:
        f.write(f"{r[0]} {r[1]} {r[2]} {r[3]}\n")

print(f"Done. Rectangles: {len(rects)}")