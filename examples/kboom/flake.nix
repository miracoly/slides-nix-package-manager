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

      packages = with pkgs; rec {
        default = kboom;
        kboom = stdenv.mkDerivation {
          pname = "kboom";
          version = "0.1.0";
          src = ./.;

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

          text = ''
            set -euo pipefail
            echo "🏗️  Building kboom …"
            make

            echo "🧪 Executing RSpec …"
            BIN=./main.out rspec --format documentation ./*.rb
          '';
        };
      };
    });
}
