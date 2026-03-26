import numpy as np
import matplotlib.pyplot as plt

def f(x, bend):
    return bend * (x - x * x / 1000) / 10

def curve(x, bend):
    fx_x = f(x, bend) + x
    return f(fx_x, bend) + fx_x

def go(value, bend):
    value = np.clip(value, -1000, 1000)
    if value >= 0:
        return curve(value, bend)
    else:
        return -curve(-value, bend)

x = np.linspace(-1000, 1000, 500)

bend_values = range(-10, 11, 2)
colors = plt.cm.tab20(np.linspace(0, 1, 20))[:11]

plt.figure(figsize=(10, 8))

for idx, bend in enumerate(bend_values):
    y = np.array([go(val, bend) for val in x])
    plt.plot(x, y, linewidth=1.5, color=colors[idx], label=f'bend = {bend}')

plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)
plt.grid(True, alpha=0.3)
plt.xlabel('Input')
plt.ylabel('Output')
plt.title('CurveDecor: Input vs Output for bend = -10..10')
plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
plt.tight_layout()

plt.savefig('images/decorators_curves.png', dpi=150, bbox_inches='tight')
print("Saved to curves.png")
