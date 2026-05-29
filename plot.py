import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("C:/Users/sande/Github/sp-exam/build/examples/out.csv")

t = df["t"]

for c in df.columns:
    plt.plot(t, df[c], label=c.capitalize())

plt.xlabel("Time (days)")
plt.ylabel("State")
plt.title("Circadian")
plt.legend()
plt.grid(alpha=0.3)
plt.tight_layout()

plt.show()
