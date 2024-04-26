mod hex;
use hex::display_hex;

mod args;
use args::parse_args;

fn main() {
  display_hex(parse_args());
}
