# wavedaq_sw — pioneer fork

A local fork of the WaveDAQ software library (`wavedaq_sw`, the `sw` submodule of
`wavedaq_main`), carrying changes needed to run a **single directly-addressed WaveDream
board** as a production MIDAS data source.

Created 2026-07-29 from `/home/pioneer/wavedaq_main/sw` at commit `1ec038f`.

## Why a fork

The waveform frontend compiles this library from source
(`add_subdirectory(${WDBSYS}/sw)` in `wavedaq_midas_frontend/CMakeLists.txt`), so whatever
`WDBSYS` points at ends up in the binary. Changes made in place would land in
`/home/pioneer/wavedaq_main`, which is the reference tree other tools and other people on
this machine still use.

The divergence is **deliberate and permanent**, not a patch queue. The upstream authors
run this library in a MEG crate with a trigger and distribution board; we run one board
on direct Ethernet with no crate at all. Several of the assumptions that are safe there
are not safe here, and the fixes are not obviously ones upstream would want.

Only the `sw` submodule is forked. The firmware, hardware, doc and linux submodules of
`wavedaq_main` are not needed to build and are not copied — 365 MB instead of 4.6 GB.

## Layout and remotes

    /home/pioneer/josh/wavedaq-pioneer/
        sw/                       the fork, branch `pioneer/standalone`
        sw/README.pioneer-fork.md this file

    local-mirror   /home/pioneer/wavedaq_main/sw   (fetch)   NO_PUSH_local_fork (push)
    upstream       bitbucket.org/twavedaq/wavedaq_sw (fetch) NO_PUSH_local_fork (push)

Both push URLs are deliberately invalid so an accidental `git push` fails loudly instead
of reaching bitbucket. Pull upstream changes with
`git fetch upstream && git merge upstream/develop` when there is a reason to.

`WDBSYS` is set to this directory by `wavedream-scalar-readout/scripts/wdscalers-env.sh`.
Nothing else needs configuring; a rebuild of the frontend picks it up.

### The fork supplies code, NOT calibration data

`config/wavedaq/online.xml` sets `<CalibPath>/home/pioneer/wavedaq_main/sw/wds</CalibPath>`
— the **original** tree, deliberately. The per-board `.vcal`/`.tcal` files live in
`wds/calib/` there and are *untracked* data, so cloning tracked history did not bring them
and this fork has no `wds/calib/`.

That works today (verified: events are being calibrated) but it is a cross-tree dependency
worth knowing about, because the failure is silent. `VCALIB::load` leaves `bValid=false` on
a missing file with no output, and the calibration arithmetic then runs with default gains
of 1 and offsets of 0 while still marking the event calibrated — so moving or cleaning
`/home/pioneer/wavedaq_main` would produce uncalibrated waveforms that are
indistinguishable from calibrated ones. See HARDENING.md Tier 4, "Calibration validity".

## Changes carried here

Each is cross-referenced to `wavedream-scalar-readout/HARDENING.md`, which records how the
problem was found, why it matters, and how the fix was verified.

| commit | item | summary |
|---|---|---|
| `970edef` | 2.4 | Remove the `DAQAlarm::Test()` data race (atomic array; ThreadSanitizer-confirmed), and stop an exception escaping `DAQThread::ThreadMain` from aborting the process. **The `Clean()` "no-op" the review reported was not real** — see HARDENING.md 2.4 |
| `bfb5935` | 2.6 | Initialise `WDAQWorker`'s statistics in its constructor; they were only zeroed in `Begin()` and read as garbage before the first run |
| `85914de` | 2.1 | Drain the socket at begin-of-run, and make the builder's two reclaim paths work after a counter reset. Without it every run began with the previous run's events and the builder could wedge for a whole run |
| `1ec038f` | — | `BuilderKey=EventNumber`: key the event builder on the board's event counter when there is no TCB, since `trigger_information` is then always zero |

See `git log pioneer/standalone` for the current list.

## Rebuilding after a change here

    cd /home/pioneer/josh/wavedream-scalar-readout && source scripts/wdscalers-env.sh
    cd /home/pioneer/josh/modern_midas/wavedaq_midas_frontend
    cmake -S . -B build && cmake --build build -j$(nproc)

The frontend's CMake cache records the absolute source path, so a build directory created
against the old `wavedaq_main` path must be deleted rather than reused.

## Calibration data lives here now (2026-07-30)

An earlier note in this file said the fork supplies code, not calibration data. That is
reversed, deliberately.

`wds/calib/` now carries the per-board `.vcal`/`.tcal` files. They previously lived only in
`/home/pioneer/wavedaq_main/sw/wds/calib/`, where they were **untracked** — a `git clean
-dfx` in that tree would have deleted the calibration our deployment depends on, and the
resulting data would have looked entirely normal (see below). Vendoring them removes the
cross-tree dependency; `config/wavedaq/online.xml` in the wdscalers repo points `CalibPath`
here.

All frequencies are included, not just the 700 MHz pair in use, so changing
`SamplingFrequency` does not silently lose calibration.

## WDBSYS in ~/.bashrc collides with this fork

`~/.bashrc:137` exports `WDBSYS=$HOME/wavedaq_main`. Anyone who runs `cmake` for the
waveform frontend **without** sourcing `wdscalers-env.sh` therefore builds against the
reference tree rather than this one. Whatever `WDBSYS` points at is compiled straight into
the binary (`add_subdirectory(${WDBSYS}/sw)`), so there is no library path to inspect
afterwards and nothing separates the two binaries at runtime.

As of 2026-07-30 the frontend's CMakeLists refuses to configure unless
`${WDBSYS}/sw/README.pioneer-fork.md` exists — i.e. unless it is pointed at this fork — and
the frontend logs both git revisions and the resolved `WDBSYS` at startup.
