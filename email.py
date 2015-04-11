#!/usr/bin/env python
from email.mime.text import MIMEText
msg = MIMEText('hello,sendby Python...','plain','utf-8')
from_addr = raw_input()
