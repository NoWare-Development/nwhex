static INVALID_USAGE_STRING: &str = "=== INVALID USAGE ===\nUsage:\n\tnwhex [flags] <file>\n\nAvailable Flags:\n\t--help -? -- display this message\n\t--ascii -A -- ASCII representation of data\n\t--output -O <file> -- output read data to a file";
static USAGE_HELP: &str =  "Usage:\n\tnwhex [flags] <file>\n\nAvailable Flags:\n\t--help -? -- display this message\n\t--ascii -A -- ASCII representation of data\n\t--output -O <file> -- output read data to a file";

pub struct Cli {
  pub pattern: Vec<String>,
  pub path: std::path::PathBuf
}

pub struct Settings {
  pub file: std::path::PathBuf,
  pub display_ascii: bool,
  pub output_to_a_file: bool,
  pub file_to_output: String
}

pub fn parse_args() -> Settings {
  let user_args = get_args();

  let mut settings = Settings {
    file: std::path::PathBuf::from(""),
    display_ascii: false,
    output_to_a_file: false,
    file_to_output: String::from("")
  };

  settings.file = user_args.path;

  let mut i = 0;
  while i < user_args.pattern.len() {
    match user_args.pattern[i].as_str() {
      "--help" => {
        panic!("{USAGE_HELP}");
      }
      "-?" => {
        panic!("{USAGE_HELP}");
      }
      "--ascii" => settings.display_ascii = true,
      "-A" => settings.display_ascii = true,
      "--out" => {
        settings.output_to_a_file = true;
        i += 1;
        settings.file_to_output = user_args.pattern[i].clone();
      }
      "-O" => {
        settings.output_to_a_file = true;
        i += 1;
        settings.file_to_output = user_args.pattern[i].clone();
      }
      &_ => {
        if !settings.output_to_a_file {
          eprintln!("Unknown argument: {}", user_args.pattern[i].as_str());
        }
      }
    };

    i += 1;
  }

  settings
}

fn get_args() -> Cli {
  let mut pattern: Vec<String> = vec![];
  let path = std::path::PathBuf::from(std::env::args().last().unwrap());
  let _ = std::env::args().nth(1).expect(INVALID_USAGE_STRING).clone();

  let arg_count = std::env::args().count();
  let mut i = 1;
  while i < arg_count - 1 {
    pattern.push(std::env::args().nth(i).unwrap());
    i += 1;
  }

  if path == std::path::PathBuf::from("--help") {
    panic!("{USAGE_HELP}");
  }

  Cli {
    pattern,
    path
  }
}
