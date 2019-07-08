import sys
import re
from html.parser import HTMLParser

ignore = {
  "PageTemplate",
  "ColorPalette",
  "DefaultTiddlers",
  "GettingStarted",
  "MainMenu",
  "PublishIndexTemplate",
  "PublishMacro",
  "PublishTemplateBody",
  "PublishTemplateBodySingle",
  "SideBarOptions",
  "SiteSubtitle",
  "SiteTitle",
  "SiteUrl",
  "StyleSheet",
  "StyleSheetColors",

  "Plug-in Architecture",
  "OpenDDS",
}

def wiki_to_md(text):
    """Convert wiki formatting to markdown formatting.
    :param text: string of text to process
    :return: processed string
    """
    fn = []
    new_text = []
    fn_n = 1  # Counter for footnotes
    for line in text.split('\n'):
        # Replace wiki headers with markdown headers
        match = re.match('(!+)(\\s?)[^\\[]', line)
        if match:
            header, spaces = match.groups()
            new_str = '#' * len(header)
            line = re.sub('(!+)(\\s?)([^\\[])', new_str + ' ' + '\\3', line)
        # Underline (doesn't exist in MD)
        line = re.sub("__(.*?)__", "\\1", line)
        # Bold
        line = re.sub("''(.*?)''", "**\\1**", line)
        # Italics
        line = re.sub("//(.*?)//", "_\\1_", line)
        # Remove wiki links
        line = re.sub("\\[\\[(\\w+?)\\]\\]", "\\1", line)
        # Change links to markdown format
        line = re.sub("\\[\\[(.*)\\|(.*)\\]\\]", "[\\1](\\2)", line)
        # Code
        line = re.sub("\\{\\{\\{(.*?)\\}\\}\\}", "`\\1`", line)
        line = re.sub("{{{", "```", line)
        line = re.sub("}}}", "```", line)
        # Footnotes
        match = re.search("```(.*)```", line)
        if match:
            text = match.groups()[0]
            fn.append(text)
            line = re.sub("```(.*)```", '[^{}]'.format(fn_n), line)
            fn_n += 1
        new_text.append(line)

    # Append footnotes
    for i, each in enumerate(fn):
        new_text.append('[^{}]: {}'.format(i+1, each))
    return '\n'.join(new_text)

class MyHTMLParser(HTMLParser):

  def handle_starttag(self, tag, attrs):
    if tag == "div":
      if self.in_store_area:
        self.div_level += 1
      for attr in attrs:
        if attr[0] == "id" and attr[1] == "storeArea":
          if self.in_store_area:
            sys.exit("Already in store area")
          self.in_store_area = True
          self.div_level = 1
        elif self.in_store_area:
          if attr[0] == "title":
            if self.title:
              sys.exit("Already in Tiddler")
            if attr[1] not in ignore:
              self.title = attr[1]
              print('## ' + self.title + "\n")
    elif tag == "pre" and self.title:
      self.in_pre = True

  def handle_endtag(self, tag):
    if self.in_store_area and tag == "div":
      self.div_level -= 1
      if self.div_level == 1:
        self.title = None 
      elif self.div_level == 0:
        self.in_store_area = False
    elif self.in_pre and tag == "pre":
      self.in_pre = False

  def handle_data(self, data):
    if self.in_pre and self.title:
      print(wiki_to_md(data))

parser = MyHTMLParser()
parser.in_store_area = False
parser.title = None
parser.div_level = 0
parser.in_pre = False
with open(sys.argv[1]) as f:
  parser.feed(f.read())
