---
Author: miracoly
date: June 25, 2025
---

# Nix Package Manager

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
