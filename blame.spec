Summary: An RCS file annotator
Name: blame
Version: 1.1
Release: 1
Copyright: GPL Version 2
Group: Development/Tools
Source0: %{name}-%{version}.tar.gz
URL: http://blame.sourceforge.net/
Vendor: Michael Chapman
Packager: Michael Chapman <foonly@users.sourceforge.net>
BuildRoot: %{_tmppath}/%{name}-%{version}-root
Prefix: %{_prefix}

%description
Blame displays the last modification for each line in an RCS file.
It is the RCS equivalent of CVS's "annotate" command.

%prep
%setup

%build
%{configure}
%{__make}
%{__make} check

%install
%{makeinstall}

%clean
if test "$RPM_BUILD_ROOT" != "/"; then
	%{__rm} -rf $RPM_BUILD_ROOT
fi

%files
%defattr(-,root,root)
%doc AUTHORS COPYING ChangeLog INSTALL NEWS README
%{_bindir}/*
%{_mandir}/*/*

%changelog

* Thu Nov 24 2004 Michael Chapman <foonly@users.sourceforge.net> 1.1-1
- Rebuilt.

* Thu Nov 24 2004 Michael Chapman <foonly@users.sourceforge.net> 1.0-3
- Said gcc 3.4 bugs weren't actually bugs.

* Thu Nov 23 2004 Michael Chapman <foonly@users.sourceforge.net> 1.0-2
- Rebuild RPM with -mtune=i386 to work around gcc 3.4 bugs.

* Thu Nov 23 2004 Michael Chapman <foonly@users.sourceforge.net> 1.0-1
- Stable release.

* Thu Nov 20 2004 Michael Chapman <foonly@users.sourceforge.net> 0.3-2
- Fixed bug involving delta texts without empty last lines.
- Fixed --help output.

* Thu Nov 11 2004 Michael Chapman <foonly@users.sourceforge.net> 0.3-1
- Support for $RCSINIT environment variable.
- Support for -V and --version to emulate old RCS versions.
- Minor bugfixes.
- Added manpage.

* Thu Oct 21 2004 Michael Chapman <foonly@users.sourceforge.net> 0.2-1
- Major speed improvements.

* Tue Sep 28 2004 Michael Chapman <foonly@users.sourceforge.net> 0.1-2
- Fixed build for old Red Hat.

* Mon Sep 27 2004 Michael Chapman <foonly@users.sourceforge.net> 0.1-1
- Initial RPM release.
