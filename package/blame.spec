%define AppProgram blame
%define AppVersion 1.3.1
%define AppRelease 20220129
Name:  %{AppProgram}
Version:  %{AppVersion}
Release:  %{AppRelease}
Summary:  annotate RCS files
License:  GPLv2
Group:  Applications/Development
URL:  https://invisible-island.net/%{AppProgram}
Source0:  %{AppProgram}-%{AppVersion}-%{AppRelease}.tgz
Packager:  Thomas E. Dickey <dickey@invisible-island.net>

%description
blame outputs an annotated revision from each RCS file.  An annotated
RCS file describes the revision and date in which each line was added
to the file, and the author of each line.

%prep

%define debug_package %{nil}

%setup -q -n %{AppProgram}-%{AppVersion}-%{AppRelease}

%build
./configure \
 --prefix=%{_prefix} \
 --exec-prefix=%{_exec_prefix} \
 --mandir=%{_mandir}
make CFLAGS="-fcommon"

%check
make check

%install
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

make install DESTDIR="$RPM_BUILD_ROOT"
# prefix=#{buildroot}#{_prefix} mandir=#{buildroot}#{_mandir}

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && rm -rf $RPM_BUILD_ROOT

%files
%license COPYING
%doc AUTHORS ChangeLog NEWS README
%{_bindir}/%{name}
%{_mandir}/man1/%{name}.1*

%changelog
# each patch should add its ChangeLog entries here

* Sun Feb 07 2021 Thomas Dickey
- initial version
