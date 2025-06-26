---
Author: miracoly
date: June 25, 2025
---

# Hier gibts nix zu sehen

![Nix Package Manager](https://upload.wikimedia.org/wikipedia/commons/3/35/Nix_Snowflake_Logo.svg) <!-- .element: class="img-small" -->

---

## Fork Repo

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

## Installation

---

### Install Nix

- go to nix' download page:
  - Linux: <https://nixos.org/download/#nix-install-linux>
  - Windows (WSL2): <https://nixos.org/download/#nix-install-windows>
- chose Multi-User installation

---

![Download nix](./img/nix-download.png)

---

- execute script

```sh
sh <(curl --proto '=https' --tlsv1.2 -L https://nixos.org/nix/...
```

- confirm with `y` when asked
- enter password if `sudo`

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
- if you're using `zsh`, run `nix develop -c zsh`
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

- nix installed
- build every project with nix
- one custom dev shell for every project

---

### Ease of development

- Problem: you need to manually run `nix develop` to enter dev shell
- Solution: `direnv` and `nix-direnv`

---

#### direnv

- shell extension
- run script on directory enter
  - e.g. load env vars

#### nix-direnv <!-- .element: class="mt-3" -->

- replacement for part of `direnv`
- allows to automatically enter nix shell

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

## Nix by Example

---

Let's skip the *"boring"* nix language part and dive right into a real world example

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

```nix [7-11]
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

# run the app
result/bin/kboom
```
