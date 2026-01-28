## renn

A tiny experimental async runtime for learning and playing with concurrency.

<!> Warning : this project exists purely for education and experimentation.

---

## What is this?

'renn' is my personal sandbox for understanding how async runtimes work inside, experimenting with different concurrency models and so on..

It's intentionally minimal, a bit weird in places, and constantly changing. The goal is to learn and try different approaches.

---

## What does it provide?

At the moment the runtime exposes a few classic building blocks:

- Fibers - lightweith units of execution
- Functional Lazy Futures - values that will (maybe) be available later
- Timers infrastructure
- Scheduling - T.O.D.O...

---

## What is a 'renn'?

While working on this, i got tired of saying "fiber/coroutine/task/job/whatever", so i "invented" my own term for "a scheduled executable unit" in this runtime.

I call it a **renn** (from the German verb **_rennen_** - "to run").

So, the scheduler doesn't really care what higher-level abstraction you use - it just submit renns.

Maybe it is mildly confusing. But i just like building abstractions.

---

This is primarily my personal playground. But if you're reading this out of curiosity, feel free to laugh at my mistakes, open an issue if something is obviously broken or unclear.
