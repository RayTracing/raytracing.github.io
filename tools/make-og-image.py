#!/usr/bin/env python3
"""Generate a 1200x630 OG image for Ray Tracing in One Weekend (raytracing.github.io).

Pillow-only, byte-reproducible. Clean technical card matching the site:
light #f0eeec ground, black text, #00f link blue / #90c purple accents,
#702000 dark-red accent, title + subtitle + book-series pills + domain.
"""
import os
from PIL import Image, ImageDraw, ImageFont

W, H = 1200, 630
BG = (240, 238, 236)          # #f0eeec site background
BLUE = (0, 0, 255)            # #00f link
PURPLE = (153, 0, 204)        # #90c
DARKRED = (112, 32, 0)        # #702000
DARK = (44, 44, 44)           # #2c2c2c
WHITE = (255, 255, 255)
GREY = (90, 90, 90)

FONT_DIR = os.environ.get("FONT_DIR", "/usr/share/fonts/truetype/dejavu")


def font(size, bold=False):
    name = "DejaVuSans-Bold.ttf" if bold else "DejaVuSans.ttf"
    p = os.path.join(FONT_DIR, name)
    if not os.path.exists(p):
        p = os.path.join(FONT_DIR, "LiberationSans-Bold.ttf" if bold else "LiberationSans-Regular.ttf")
    return ImageFont.truetype(p, size)


def rounded(d, box, r, fill):
    d.rounded_rectangle(box, radius=r, fill=fill)


def main():
    img = Image.new("RGB", (W, H), BG)
    d = ImageDraw.Draw(img)

    # top accent bar (dark red)
    d.rectangle([0, 0, W, 10], fill=DARKRED)

    f_title = font(64, bold=True)
    f_sub = font(34)
    f_pill = font(28, bold=True)
    f_domain = font(30, bold=True)
    f_foot = font(24)

    d.text((70, 70), "Ray Tracing in One Weekend", font=f_title, fill=DARK)
    d.text((70, 160), "The Book Series", font=f_sub, fill=GREY)

    # separator
    d.line([70, 250, W - 70, 250], fill=(200, 196, 190), width=2)

    # book-series pills
    pills = ["Ray Tracing in One Weekend", "The Next Week", "The Rest of Your Life"]
    x = 70
    y = 290
    for p_ in pills:
        w = d.textlength(p_, font=f_pill) + 44
        if x + w > 1130:  # wrap to next row before overflow
            x = 70
            y += 82
        rounded(d, [x, y, x + w, y + 62], 31, BLUE)
        d.text((x + 22, y + 13), p_, font=f_pill, fill=WHITE)
        x += w + 18

    # footer domain chip
    d.rounded_rectangle([70, H - 92, 470, H - 44], 24, fill=DARK)
    d.text((108, H - 84), "raytracing.github.io", font=f_domain, fill=WHITE)

    # subtle line-art: a ray-tracing sphere motif (circle + light ray)
    cx, cy = W - 200, H - 150
    d.ellipse([cx - 60, cy - 60, cx + 60, cy + 60], outline=PURPLE, width=4)
    d.line([cx + 60, cy, cx + 150, cy - 40], fill=PURPLE, width=4)
    d.ellipse([cx + 140, cy - 50, cx + 160, cy - 30], fill=PURPLE)

    out = "og-image.png"
    img.save(out, "PNG")
    print("wrote", out, img.size)


if __name__ == "__main__":
    main()
