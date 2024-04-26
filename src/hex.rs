use crate::args::Settings;

use std::fs::File;
use std::io::Write;
use std::fs;

static TEMPLATE_STRINGS: [&str; 4] = [
  "| Address    | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F |\n",
  "| ---------- | ----------------------------------------------- |\n",
  "| ---------- | ----------------------------------------------- | ---------------- |\n",
  "| Address    | 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F | ASCII            |\n",
];

fn print_new_line_start(index: usize, output: &mut Vec<String>) {
  if index > 0 {
    output.push(format!("|\n| {:#010X} | ", index));
  }
  else {
    output.push(format!("| {:#010X} | ", index));
  }
}

pub fn display_hex(settings: Settings) {
  let mut output: Vec<String> = vec![];
  let content = fs::read(settings.file.clone()).expect("Given file is empty");

  if settings.display_ascii {
    output.push(String::from(TEMPLATE_STRINGS[3]));
    output.push(String::from(TEMPLATE_STRINGS[2]));
  }
  else {
    output.push(String::from(TEMPLATE_STRINGS[0]));
    output.push(String::from(TEMPLATE_STRINGS[1]));
  }

  let mut index = 0 as usize;
  while index < content.len() {
    if index % 0x10 == 0 {
      if index > 0 {
        if settings.display_ascii {
          output.push("| ".to_owned());
          let mut buffered_index = index - 0x10;
          while buffered_index != index {
            if content[buffered_index] < 32u8 ||
               content[buffered_index] > 126u8 {
              output.push(".".to_owned());
            }
            else {
              output.push(format!("{}", content[buffered_index] as char));
            }
            buffered_index += 1;
          }

          output.push(" ".to_owned());
          print_new_line_start(index, &mut output);
        }
        else {
          print_new_line_start(index, &mut output);
        }
      }
      else {
        print_new_line_start(index, &mut output);
      }
    }

    output.push(format!("{:02X} ", content[index]));
    if index == content.len() - 1 {
      let last_index = index;
      let remain = index - (index % 0x10);

      index += 1;

      while index % 0x10 != 0 {
        output.push("   ".to_owned());
        index += 1;
      }
      output.push("|".to_owned());

      if settings.display_ascii {
        output.push(" ".to_owned());
        let mut buffered_index = remain;
        while buffered_index != last_index {
          if content[buffered_index] < 32u8 || content[buffered_index] > 126u8 {
            output.push(".".to_owned());
          }
          else {
            output.push(format!("{}", content[buffered_index] as char));
          }
          buffered_index += 1;
        }

        while buffered_index != index {
          output.push(" ".to_owned());
          buffered_index += 1;
        }

        output.push(" |".to_owned());
      }

      output.push("\n".to_owned());
    }

    index += 1;
  }

  if settings.output_to_a_file {
    print_to_a_file(output.clone(), settings);
  }

  for s in output {
    print!("{s}");
  }
}

fn print_to_a_file(output: Vec<String>, settings: Settings) {
  let mut file = File::create(settings.file_to_output.clone())
    .expect("Failed to create/open output file");

  for s in output {
    write!(&mut file, "{s}").expect("Failed to write to output file");
  }
}
