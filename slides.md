---
Author: miracoly
date: June 25, 2025
---

# Hier gibts nix zu sehen

![Nix Package Manager](https://upload.wikimedia.org/wikipedia/commons/3/35/Nix_Snowflake_Logo.svg) <!-- .element: class="img-small" -->
> Laptop needed by everyone

---

> Please wait until the end of the presentation to ask questions.

---

The Problem

## Dependencies <!-- .element: class="fragment" -->

- libraries <!-- .element: class="fragment" -->
- tools to build software <!-- .element: class="fragment" -->
- tooling for local development <!-- .element: class="fragment" -->

---

### UDP Gütersloh

- k8s, helm, fluxcd, minikube, k9s <!-- .element: class="fragment" -->
- bruno, gradle, kotlin, jq, openssl, sops <!-- .element: class="fragment" -->
- telepresence in specific version <!-- .element: class="fragment" -->
- playwright with browsers <!-- .element: class="fragment" -->
- many env vars for e2e tests <!-- .element: class="fragment" -->

---

### Control Center

- terraform, yarn, socat, lens <!-- .element: class="fragment" -->
- azurecli in specific version <!-- .element: class="fragment" -->
- gauge, taiko <!-- .element: class="fragment" -->
- cypress with browsers <!-- .element: class="fragment" -->

---

### Apprentice Program

- asciidoctor-pdf <!-- .element: class="fragment" -->
- gitlint, pnpm <!-- .element: class="fragment" -->
- ruby <!-- .element: class="fragment" -->

---

### Academy Day Presentation

When you want to present a non‑trivial project you often spend more time on setup than on slides. <!-- .element: class="fragment" -->

- C/C++, Haskell, Go, Python <!-- .element: class="fragment" -->
- configuring your machine <!-- .element: class="fragment" -->

---

### Situation

To run a project you must install all of its dependencies <!-- .element: class="fragment" -->

- every developer <!-- .element: class="fragment" -->
- on every machine <!-- .element: class="fragment" -->
- including CI - which can be pain <!-- .element: class="fragment" -->

---

When dependencies are added or updated

- you repeat the whole process <!-- .element: class="fragment" -->
- you might break the pipeline <!-- .element: class="fragment" -->
- it still may not work on for all colleagues <!-- .element: class="fragment" -->

---

Adding dependencies differ per system and language

- `apt`, `pacman`, `yum`, `brew`
- `pip`, `npm`, `yarn`, `gem`, `cargo`, `mvn`
- bash-scripts

---

Solution

![Nix logo](https://upload.wikimedia.org/wikipedia/commons/3/35/Nix_Snowflake_Logo.svg) <!-- .element: class="img-small fragment" -->

---

## Nix

- declarative - one file to rule them all <!-- .element: class="fragment" -->
  - libs, tools, versions <!-- .element: class="fragment" -->
- language agnostic <!-- .element: class="fragment" -->
  - C-libs, Python, Go, Haskell, Node-modules <!-- .element: class="fragment" -->
- multiple versions of the same program? <!-- .element: class="fragment" -->
  - no problem - nix has you covered <!-- .element: class="fragment" -->
- reproducible builds <!-- .element: class="fragment" -->

---

- own language for describing packages
- many domain specific languages for many use cases <!-- .element: class="fragment" -->
  - VHDL for hardware
  - many software languages
  - Solidity for smart contracts
- nix language describes how to create derivations <!-- .element: class="fragment" -->
  - derivations are build instructions

---

Let's skip the *"boring"* theory and dive right into a real world example

---

## Fork the Repository

---

<https://github.com/miracoly/slides-nix-package-manager>

![Fork repo](./img/fork-repo.png)

---

![Create fork](./img/create-fork.png)

---

```sh
git clone https://github.com/<YOUR_USERNAME>/slides-nix-package-manager
```

![Clone repo](./img/clone-repo.png) <!-- .element: class="img-small" -->

---

### Install IntelliJ Plugin

- [NixIDEA by NixOS](https://plugins.jetbrains.com/plugin/8607-nixidea)

---

## Installation

---

### Install Nix

- go to the nix download page:
  - Linux: <https://nixos.org/download/#nix-install-linux>
  - Windows (WSL2): <https://nixos.org/download/#nix-install-windows>
- choose the multi-user installation

---

![Download nix](./img/nix-download.png)

---

- execute script

```sh
sh <(curl --proto '=https' --tlsv1.2 -L https://nixos.org/nix/...
```

- confirm with `y` when prompted
- enter password if `sudo` asks

---

### Enable Flakes

*/etc/nix/nix.conf*

```env [15-17]
experimental-features = nix-command flakes
```

---

### Sanity Check 1

```nix [6-11]
{
  outputs = { /* ... */ }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      apps.default = {
        type = "app";
        program = toString (pkgs.writeShellScript "nix-check" ''
          echo "✅ Nix flakes are working on ${system}!"
        '');
      };
      devShells.default = pkgs.mkShell {
        packages = [pkgs.hello];
        shellHook = ''
          echo "🛠️  Welcome to the Nix dev shell (${system})"
          echo "Try running: hello"
        '';
      };
    });
}
```

---

- navigate to `examples/sanity-check`
- run `nix run`

```sh
$ nix run
✅ Nix flakes are working on x86_64-linux!
```

---

### Sanity Check 2

```nix [12-18]
{
  outputs = { /* ... */ }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      apps.default = {
        type = "app";
        program = toString (pkgs.writeShellScript "nix-check" ''
          echo "✅ Nix flakes are working on ${system}!"
        '');
      };
      devShells.default = pkgs.mkShell {
        packages = [pkgs.hello];
        shellHook = ''
          echo "🛠️  Welcome to the Nix dev shell (${system})"
          echo "Try running: hello"
        '';
      };
    });
}
```

---

- run `hello`
  - expected behavior: `command not found: 'hello'`
- run `nix develop` to enter the dev shell
  - for `zsh`, run `nix develop -c zsh`
- run `hello` again

```sh
$ hello
Hello, world!
```

---

- press `Ctrl-D` to exit dev shell
- run `hello` again
- as before `command not found: 'hello'`

---

### What we've achieved

- nix installed ✅
- we’re now ready to build with Nix and set up development environments ✅

---

## Nix by Example

---

### KBOOM

```sh
$ ./kboom
kboom — big-integer maths demo (GNU MP powered)

Usage:
  ./kboom factorial | fa   <n>
  ./kboom fibonacci | fi   <n>
  ./kboom sumsquare | s    <n>
  ./kboom -h | --help

<n> must be a non-negative integer (GMP handles arbitrarily large values).
```

---

### Preview

---

### Build it locally

```sh  
cd examples/kboom
# from now on, we'll do everything in this dir
make
```

---

- do you have `make` available?
- what about lib `gmp` for big ints?
- do you even have `gcc`?

---

### Create a dev shell

---

#### Define Inputs

*examples/kboom/flake.nix*

```nix
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };
}
```

---

Define outputs

```nix [6-10]
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }: {};
}
```

---

Support each default system

```nix [4, 12-14]
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-25.05";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {});
}
```

---

Define default dev shell

```nix [10-17]
{
  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gcc
          gdb
          gmp
          gnumake
        ];
      };
    });
}
```

---

### Try building again

```sh
# enter dev shell
nix develop -c zsh
# build kboom
make

# run the app
./main.out
```

---

### Where do these packages come from?

---

- <https://search.nixos.org/packages>

![Search Nix Packages](./img/nix-pkgs-search.png)

---

- <https://github.com/NixOS/nixpkgs>

![gnumake Derivation](./img/gnumake-drv.png)

---

### Build with nix

---

Let's create a package

```sh [12 -14]
{
  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {};

      packages = with pkgs; {
        kboom = stdenv.mkDerivation {};
      };
    });
}
```

---

Define metadata

```sh [7-9]
{
  outputs = {}: {
      devShells.default = pkgs.mkShell {};

      packages = with pkgs; {
        kboom = stdenv.mkDerivation {
          pname = "kboom";
          version = "0.1.0";
          src = ./.;
        };
      };
    });
}
```

---

Define build dependencies

```sh [11-12]
{
  outputs = {}: {
      devShells.default = pkgs.mkShell {};

      packages = with pkgs; {
        kboom = stdenv.mkDerivation {
          pname = "kboom";
          version = "0.1.0";
          src = ./.;

          buildInputs = [gmp];
          nativeBuildInputs = [gcc gnumake];
        };
      };
    });
}
```

---

Define build steps

```sh [9-15]
{
  outputs = {}: {
      packages = with pkgs; {
        kboom = stdenv.mkDerivation {
          # ...
          buildInputs = [gmp];
          nativeBuildInputs = [gcc gnumake];

          buildPhase = ''
            make
          '';
          installPhase = ''
            mkdir -p $out/bin
            cp main.out $out/bin/kboom
          '';
        };
      };
    });
}
```

---

#### Let's build it

```txt
# inside examples/kboom
nix build .\#kboom
```

```sh
# inside examples/kboom

# out build output
ls -la result/bin/kboom
```

---

Make kboom our default app

```nix [6-9]
{
  outputs = {}:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      packages = with pkgs; rec {
        default = kboom;
        kboom = stdenv.mkDerivation {};
      };
    });
}
```

---

Build again and run

```sh
# inside examples/kboom
nix build

# run the app, either
result/bin/kboom
# or
nix run
```

---

### E2E tests

- `examples/kboom/kboom.spec.rb`
- executes the app and expects correct `stdout`
- dependencies: `rspec`

---

#### dev shell

```nix [12]
{
  outputs = { }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {
        nativeBuildInputs = with pkgs; [
          gcc
          gdb
          gmp
          gnumake
          rubyPackages.rspec
        ];
      };
    });
}
```

---

#### run tests from shell

```sh
# inside examples/kboom

# main.out is expected
make
# run tests
rspec ./*.rb

```

---

- great for local development, but requires `main.out` to be present
- what about a self-contained way of running e2e tests? <!-- .element: class="fragment" -->
  - necessary for CI <!-- .element: class="fragment" -->

---

#### Shell Application

```nix [7-9]
{
  outputs = {}: {
      packages = with pkgs; rec {
        default = kboom;
        kboom = stdenv.mkDerivation {};

        test = pkgs.writeShellApplication {
          name = "kboom-tests";
        };
      };
    });
}
```

---

Dependencies

```nix [7-14]
{
  outputs = {}: {
      packages = with pkgs; rec {
        test = pkgs.writeShellApplication {
          name = "kboom-tests";

          runtimeInputs = with pkgs; let
            rubyWithRSpec = pkgs.ruby.withPackages (ps: [ps.rspec]);
          in [
            gcc
            gnumake
            gmp
            rubyWithRSpec
          ];
        };
      };
    });
}
```

---

Actual script

```nix [4, 8-12]
{
  outputs = {}: {
      packages = with pkgs; rec {
        kboom = stdenv.mkDerivation {};
        test = pkgs.writeShellApplication {
          name = "kboom-tests";
          runtimeInputs = [...];
          text = ''
            set -euo pipefail
            echo "🧪 Executing RSpec …"
            BIN=${kboom}/bin/kboom rspec --format documentation ./*.rb
          '';
        };
      };
    });
}
```

---

Run self-contained tests

```sh
$ nix run .\#test

Finished in 0.01153 seconds (files took 0.05594 seconds to load)
6 examples, 0 failures
```

---

#### Infinite Possibilities

- linting <!-- .element: class="fragment" -->
  - gitlint <!-- .element: class="fragment" -->
  - markdownlint, clang-tidy <!-- .element: class="fragment" -->
  - hadolint for Dockerfiles <!-- .element: class="fragment" -->
- formatting <!-- .element: class="fragment" -->
  - prettier <!-- .element: class="fragment" -->
  - dockerfmt <!-- .element: class="fragment" -->
  - ormolu <!-- .element: class="fragment" -->
- testing <!-- .element: class="fragment" -->
  - playwright <!-- .element: class="fragment" -->
  - gtest <!-- .element: class="fragment" -->

---

### Pipeline

- everyone can do everything locally — great! <!-- .element: class="fragment" -->
- but can we go further? <!-- .element: class="fragment" -->
- what about building, linting, and testing in the pipeline? <!-- .element: class="fragment" -->

---

#### Let's create a simple validation pipeline

---

*.github/workflows/validation.yaml*

```yaml
name: Validation

on:
  push:

jobs:
  validate:
    name: Validate
    runs-on: ubuntu-latest
```

---

Checkout and install nix with caching

```yaml [11-17]
name: Validation

on:
  push:

jobs:
  validate:
    name: Validate
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - name: Install Nix
        uses: cachix/install-nix-action@v21
        with:
          github_access_token: ${{ secrets.GITHUB_TOKEN }}
```

---

Show version and check flake

```yaml [10-14]
jobs:
  validate:
    steps:
      - uses: actions/checkout@v4
      - name: Install Nix
        uses: cachix/install-nix-action@v21
        with:
          github_access_token: ${{ secrets.GITHUB_TOKEN }}

      - name: Show nix version
        run: nix --version

      - name: Check flake
        run: nix flake check
```

---

Commit and Push

![CI Flake check](./img/ci-flake-check.png)

---

```yaml [9-15]
jobs:
  validate:
    steps:
      - name: Show nix version
        run: nix --version
      - name: Check flake
        run: nix flake check

      - name: Build
        working-directory: examples/kboom
        run: nix build .#kboom

      - name: Test
        working-directory: examples/kboom
        run: nix run .#test
```

---

Commit and Push

![Ci Green](./img/ci-green.png)

---

### Some additional hints

---

#### Adhoc shell

- sometimes you temporally need a program, but don't want to install it

```sh
$ nix shell nixpkgs\#hello-go -c zsh
$ hello-go
Hello, world!
```

---

#### Clean up

- nix stores all derivations in `/nix/store/`
- one derivation per version for each program
- over time, this can consume a lot of disk space

```sh
sudo nix-collect-garbage --delete-older-than 90d
```

---

#### Jetbrains IDE's and Co

```bash
# in development shell
$ nohup idea-ultimate &
```

---

### Ease of development

- Problem: you need to manually run `nix develop` to enter dev shell
- Solution: `direnv` and `nix-direnv`

---

#### direnv

- shell extension <!-- .element: class="fragment" -->
- execute scripts when you enter a directory <!-- .element: class="fragment" -->
  - e.g. load env vars <!-- .element: class="fragment" -->

#### nix-direnv <!-- .element: class="mt-3 fragment" -->

- replacement for part of direnv <!-- .element: class="fragment" -->
- automatically enters nix shell <!-- .element: class="fragment" -->

---

#### Install direnv

- [direnv for Ubuntu](https://packages.ubuntu.com/search?keywords=direnv&searchon=names&suite=all&section=all)

```
sudo apt install direnv
```

---

#### Hook direnv into your shell

*$HOME/.bashrc*

```rc
eval "$(direnv hook bash)"
```

*$HOME/.zshrc*

```rc
eval "$(direnv hook zsh)"
```

Which shell do I use?

```bash
 echo $0
```

---

#### Install nix-direnv

```sh
nix profile install nixpkgs#nix-direnv
```

#### Add nix-direnv to direnvrc <!-- .element: class="mt-3" -->

*$HOME/.config/direnv/direnvrc*

```rc
source $HOME/.nix-profile/share/nix-direnv/direnvrc
```

---

#### Use direnv

- close and reopen your terminal
- run the following command:

```bash
cd example/sanity-check
# tell direnv to use flakes
echo "use flake" >> .envrc
# allow to automatically enter dev shell for this dir
direnv allow
```

---

#### Test direnv

- now you should automatically enter the dev shell
- validate with:

```sh
# navigate to your home dir
cd ~
# navigate to previous dir (examples/sanity-check)
cd -
```

---

#### Silent direnv output

*$HOME/.config/direnv/direnv.toml*

```toml
[global]
log_filter = "^$"
log_format = "-"
```

---

## Where to go from here?

---

- this was just the tip of the iceberg
- many things were left out: <!-- .element: class="fragment" -->
  - the classic nix vs. flakes debate <!-- .element: class="fragment" -->
  - nix language quirks and specifics <!-- .element: class="fragment" -->
- the nix rabbit hole is deep — very deep <!-- .element: class="fragment" -->
- and the documentation... well, it’s not exactly great <!-- .element: class="fragment" -->

---

### Learn more

- [nix.dev](https://nix.dev/)
- [NixOS & Flakes Book](https://nixos-and-flakes.thiscute.world/)
- [Videos by Vimjoyer 🎥](https://www.youtube.com/watch?v=9OMDnZWXjn4)
- ask [our lord and savior 🤖](https://chatgpt.com/)
- NixOS as Linux Distribution

---

### Takeaways for our company

- start by providing simple dev shells <!-- .element: class="fragment" -->
- this is especially helpful for part-time projects <!-- .element: class="fragment" -->
  - e.g. apprentice guide, kb app, wheel of fun <!-- .element: class="fragment" -->
- write simple shell apps for linting and formatting <!-- .element: class="fragment" -->
  - use in CI Pipeline <!-- .element: class="fragment" -->

---

## Thank you

---

## Questions?
