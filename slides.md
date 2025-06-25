---
Author: miracoly
date: January 19, 2021
---

# Nix Package Manager

![Nix Package Manager](https://upload.wikimedia.org/wikipedia/commons/3/35/Nix_Snowflake_Logo.svg) <!-- .element: class="img-small" -->

---

## Hands On - Installation

---

### Installiere Nix

- gehe zur nix Download Seite:
  - Linux: <https://nixos.org/download/#nix-install-linux>
  - Windows (WSL2): <https://nixos.org/download/#nix-install-windows>
- wähle Multi-User installation

---

![Download nix](./img/nix-download.png)

---

- Script ausführen
- mit `y` bestätigen
- bei `sudo` password eingeben

---

```nix [15-17]
  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
    in {
      devShells.default = pkgs.mkShell {
        buildInputs = [
          pkgs.nodejs_22
          pkgs.nodePackages.reveal-md
        ];

        shellHook = ''
          echo -e "hi"
        '';
      };
```

---
